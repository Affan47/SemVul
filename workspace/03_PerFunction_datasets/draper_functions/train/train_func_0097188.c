hdb_start_seq_get(krb5_context context,
		  krb5_keytab id,
		  krb5_kt_cursor *cursor)
{
    krb5_error_code ret;
    struct hdb_cursor *c;
    struct hdb_data *d = id->data;
    const char *dbname = d->dbname;
    const char *mkey   = d->mkey;
    HDB *db;

    if (dbname == NULL) {


  	ret = KRB5_KT_NOTFOUND;
	return ret;
    }

    ret = hdb_create (context, &db, dbname);
    if (ret)
	return ret;
    ret = hdb_set_master_keyfile (context, db, mkey);
    if (ret) {
	(*db->hdb_destroy)(context, db);
	return ret;
    }

    ret = (*db->hdb_open)(context, db, O_RDONLY, 0);
    if (ret) {
	(*db->hdb_destroy)(context, db);
	return ret;
    }

    cursor->data = c = malloc (sizeof(*c));
    if(c == NULL){
	(*db->hdb_close)(context, db);
	(*db->hdb_destroy)(context, db);
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    c->db = db;
    c->first = TRUE;
    c->next = TRUE;
    c->key_idx = 0;

    cursor->data = c;
    return ret;
}
