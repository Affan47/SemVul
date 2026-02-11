krb5_dbe_find_act_mkey(krb5_context context, krb5_actkvno_node *act_mkey_list,
                       krb5_kvno *act_kvno, krb5_keyblock **act_mkey)
{
    krb5_kvno kvno;
    krb5_error_code retval;
    krb5_keyblock *mkey, *cur_mkey;
    krb5_timestamp now;

    if (act_mkey_list == NULL) {
        *act_kvno = 0;
        *act_mkey = NULL;
        return 0;
    }

    if (context->dal_handle->master_keylist == NULL)
        return KRB5_KDB_DBNOTINITED;


    if ((retval = krb5_timeofday(context, &now)))
        return (retval);
    kvno = find_actkvno(act_mkey_list, now);


    mkey = find_master_key(context, kvno);
    if (mkey == NULL) {

        cur_mkey = &context->dal_handle->master_keylist->keyblock;
        if (krb5_db_fetch_mkey_list(context, context->dal_handle->master_princ,
                                    cur_mkey) == 0)
            mkey = find_master_key(context, kvno);
    }
    if (mkey == NULL)
        return KRB5_KDB_NO_MATCHING_KEY;

    *act_mkey = mkey;
    if (act_kvno != NULL)
        *act_kvno = kvno;
    return 0;
}
