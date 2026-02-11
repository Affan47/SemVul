store_principal_ent(krb5_context contextp,
		    krb5_storage *sp,
		    kadm5_principal_ent_rec *ent)
{
    int i;

    CHECK(store_principal_xdr(contextp, sp, ent->principal));
    CHECK(krb5_store_uint32(sp, ent->princ_expire_time));
    CHECK(krb5_store_uint32(sp, ent->pw_expiration));
    CHECK(krb5_store_uint32(sp, ent->last_pwd_change));
    CHECK(krb5_store_uint32(sp, ent->max_life));
    CHECK(krb5_store_int32(sp, ent->mod_name == NULL));
    if (ent->mod_name)
	CHECK(store_principal_xdr(contextp, sp, ent->mod_name));
    CHECK(krb5_store_uint32(sp, ent->mod_date));
    CHECK(krb5_store_uint32(sp, ent->attributes));
    CHECK(krb5_store_uint32(sp, ent->kvno));
    CHECK(krb5_store_uint32(sp, ent->mkvno));
    CHECK(store_string_xdr(sp, ent->policy));
    CHECK(krb5_store_int32(sp, ent->aux_attributes));
    CHECK(krb5_store_int32(sp, ent->max_renewable_life));
    CHECK(krb5_store_int32(sp, ent->last_success));
    CHECK(krb5_store_int32(sp, ent->last_failed));
    CHECK(krb5_store_int32(sp, ent->fail_auth_count));
    CHECK(krb5_store_int32(sp, ent->n_key_data));
    CHECK(krb5_store_int32(sp, ent->n_tl_data));
    CHECK(krb5_store_int32(sp, ent->n_tl_data == 0));
    if (ent->n_tl_data) {
	krb5_tl_data *tp;

	for (tp = ent->tl_data; tp; tp = tp->tl_data_next) {
	    krb5_data c;
	    c.length = tp->tl_data_length;
	    c.data = tp->tl_data_contents;

	    CHECK(krb5_store_int32(sp, 0));
	    CHECK(krb5_store_int32(sp, tp->tl_data_type));
	    CHECK(store_data_xdr(sp, c));
	}
	CHECK(krb5_store_int32(sp, 1));
    }

    CHECK(krb5_store_int32(sp, ent->n_key_data));
    for (i = 0; i < ent->n_key_data; i++) {
	CHECK(krb5_store_uint32(sp, 2));
	CHECK(krb5_store_uint32(sp, ent->kvno));
	CHECK(krb5_store_uint32(sp, ent->key_data[i].key_data_type[0]));
	CHECK(krb5_store_uint32(sp, ent->key_data[i].key_data_type[1]));
    }

    return 0;
}
