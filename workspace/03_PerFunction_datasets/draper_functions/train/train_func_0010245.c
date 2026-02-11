kadm5_s_randkey_principal(void *server_handle,
			  krb5_principal princ,
			  krb5_boolean keepold,
			  int n_ks_tuple,
			  krb5_key_salt_tuple *ks_tuple,
			  krb5_keyblock **new_keys,
			  int *n_keys)
{
    kadm5_server_context *context = server_handle;
    hdb_entry_ex ent;
    kadm5_ret_t ret;

    memset(&ent, 0, sizeof(ent));
    if (!context->keep_open) {
	ret = context->db->hdb_open(context->context, context->db, O_RDWR, 0);
	if(ret)
	    return ret;
    }
    ret = context->db->hdb_fetch_kvno(context->context, context->db, princ,
				      HDB_F_GET_ANY|HDB_F_ADMIN_DATA, 0, &ent);
    if(ret)
	goto out;

    if (keepold) {
	ret = hdb_add_current_keys_to_history(context->context, &ent.entry);
	if (ret)
	    goto out2;
    }

    ret = _kadm5_set_keys_randomly (context,
				    &ent.entry,
				    n_ks_tuple,
				    ks_tuple,
				    new_keys,
				    n_keys);
    if (ret)
	goto out2;
    ent.entry.kvno++;

    ent.entry.flags.require_pwchange = 0;

    ret = _kadm5_set_modifier(context, &ent.entry);
    if(ret)
	goto out3;
    ret = _kadm5_bump_pw_expire(context, &ent.entry);
    if (ret)
	goto out2;

    if (keepold) {
	ret = hdb_seal_keys(context->context, context->db, &ent.entry);
	if (ret)
	    goto out2;
    } else {
	HDB_extension ext;

	memset(&ext, 0, sizeof (ext));
	ext.data.element = choice_HDB_extension_data_hist_keys;
	ext.data.u.hist_keys.len = 0;
	ext.data.u.hist_keys.val = NULL;
	hdb_replace_extension(context->context, &ent.entry, &ext);
    }

    ret = context->db->hdb_store(context->context, context->db,
				 HDB_F_REPLACE, &ent);
    if (ret)
	goto out2;

    kadm5_log_modify(context, &ent.entry,
		     KADM5_ATTRIBUTES | KADM5_PRINCIPAL | KADM5_MOD_NAME |
		     KADM5_MOD_TIME | KADM5_KEY_DATA | KADM5_KVNO |
		     KADM5_PW_EXPIRATION | KADM5_TL_DATA);

out3:
    if (ret) {
	int i;

	for (i = 0; i < *n_keys; ++i)
	    krb5_free_keyblock_contents (context->context, &(*new_keys)[i]);
	free (*new_keys);
	*new_keys = NULL;
	*n_keys = 0;
    }
out2:
    hdb_free_entry(context->context, &ent);
out:
    if (!context->keep_open)
	context->db->hdb_close(context->context, context->db);
    return _kadm5_error_code(ret);
}
