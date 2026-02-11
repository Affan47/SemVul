write_dump (krb5_context context, krb5_storage *dump,
	    const char *database, uint32_t current_version)
{
    krb5_error_code ret;
    krb5_storage *sp;
    HDB *db;
    krb5_data data;
    char buf[8];


    ret = krb5_storage_truncate(dump, 0);
    if (ret)
	return ret;


    ret = krb5_store_uint32(dump, 0);

    ret = hdb_create (context, &db, database);
    if (ret)
	krb5_err (context, 1, ret, "hdb_create: %s", database);
    ret = db->hdb_open (context, db, O_RDONLY, 0);
    if (ret)
	krb5_err (context, 1, ret, "db->open");

    sp = krb5_storage_from_mem (buf, 4);
    if (sp == NULL)
	krb5_errx (context, 1, "krb5_storage_from_mem");
    krb5_store_int32 (sp, TELL_YOU_EVERYTHING);
    krb5_storage_free (sp);

    data.data   = buf;
    data.length = 4;

    ret = krb5_store_data(dump, data);
    if (ret) {
	krb5_warn (context, ret, "write_dump");
	return ret;
    }

    ret = hdb_foreach (context, db, HDB_F_ADMIN_DATA, dump_one, dump);
    if (ret) {
	krb5_warn (context, ret, "write_dump: hdb_foreach");
	return ret;
    }

    (*db->hdb_close)(context, db);
    (*db->hdb_destroy)(context, db);

    sp = krb5_storage_from_mem (buf, 8);
    if (sp == NULL)
	krb5_errx (context, 1, "krb5_storage_from_mem");
    krb5_store_int32 (sp, NOW_YOU_HAVE);
    krb5_store_int32 (sp, current_version);
    krb5_storage_free (sp);

    data.length = 8;

    ret = krb5_store_data(dump, data);
    if (ret) {
	krb5_warn (context, ret, "write_dump");
	return ret;
    }


    ret = krb5_storage_fsync(dump);
    if (ret == -1) {
	ret = errno;
	krb5_warn(context, ret, "syncing iprop dumpfile");
	return ret;
    }

    ret = krb5_storage_seek(dump, 0, SEEK_SET);
    if (ret == -1) {
	ret = errno;
	krb5_warn(context, ret, "krb5_storage_seek(dump, 0, SEEK_SET)");
	return ret;
    }


    ret = krb5_store_uint32(dump, current_version);
    if (ret) {
	krb5_warn(context, ret, "writing version to dumpfile");
	return ret;
    }


    krb5_warnx(context, "wrote new dumpfile (version %u)", current_version);

    return 0;
}
