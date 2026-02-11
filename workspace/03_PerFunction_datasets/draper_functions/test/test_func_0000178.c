krb5_def_store_mkey_list(krb5_context       context,
                         char               *keyfile,
                         krb5_principal     mname,
                         krb5_keylist_node  *keylist,
                         char               *master_pwd)
{
    krb5_error_code retval = 0;
    char defkeyfile[MAXPATHLEN+1];
    char *tmp_ktname = NULL, *tmp_ktpath;
    krb5_data *realm = krb5_princ_realm(context, mname);
    krb5_keytab kt = NULL;
    krb5_keytab_entry new_entry;
    struct stat stb;
    int statrc;

    if (!keyfile) {
        (void) snprintf(defkeyfile, sizeof(defkeyfile), "%s%s",
                        DEFAULT_KEYFILE_STUB, realm->data);
        keyfile = defkeyfile;
    }


    if ((statrc = stat(keyfile, &stb)) >= 0) {

        if (!S_ISREG(stb.st_mode)) {
            retval = EINVAL;
            krb5_set_error_message(context, retval,
                                   _("keyfile (%s) is not a regular file: %s"),
                                   keyfile, error_message(retval));
            goto out;
        }
    }


    if ((retval = asprintf(&tmp_ktname, "WRFILE:%s_XXXXXX", keyfile)) < 0) {
        krb5_set_error_message(context, retval,
                               _("Could not create temp keytab file name."));
        goto out;
    }


    tmp_ktpath = tmp_ktname + (sizeof("WRFILE:") - 1);

    if (mktemp(tmp_ktpath) == NULL) {
        retval = errno;
        krb5_set_error_message(context, retval,
                               _("Could not create temp stash file: %s"),
                               error_message(errno));
        goto out;
    }


    retval = krb5_kt_resolve(context, tmp_ktname, &kt);
    if (retval != 0)
        goto out;

    while (keylist && !retval) {
        memset(&new_entry, 0, sizeof(new_entry));
        new_entry.principal = mname;
        new_entry.key = keylist->keyblock;
        new_entry.vno = keylist->kvno;

        retval = krb5_kt_add_entry(context, kt, &new_entry);
        keylist = keylist->next;
    }
    krb5_kt_close(context, kt);

    if (retval != 0) {

        if (stat(keyfile, &stb) >= 0)
            (void) unlink(tmp_ktpath);
    } else {

        if (rename(tmp_ktpath, keyfile) < 0) {
            retval = errno;
            krb5_set_error_message(context, retval,
                                   _("rename of temporary keyfile (%s) to "
                                     "(%s) failed: %s"), tmp_ktpath, keyfile,
                                   error_message(errno));
        }
    }

out:
    if (tmp_ktname != NULL)
        free(tmp_ktname);

    return retval;
}
