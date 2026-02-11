ec_key_generate(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
#if defined(HAVE_EC)
    EC_KEY *key = ec_key_new(env, argv[0]);

    if (key && EC_KEY_generate_key(key)) {
	const EC_GROUP *group;
	const EC_POINT *public_key;
	ERL_NIF_TERM priv_key;
	ERL_NIF_TERM pub_key = atom_undefined;

	group = EC_KEY_get0_group(key);
	public_key = EC_KEY_get0_public_key(key);

	if (group && public_key) {
	    pub_key = point2term(env, group, public_key,
				 EC_KEY_get_conv_form(key));
	}
	priv_key = bn2term(env, EC_KEY_get0_private_key(key));
	EC_KEY_free(key);
	return enif_make_tuple2(env, pub_key, priv_key);
    }
    else
	return enif_make_badarg(env);
#else
    return atom_notsup;
#endif
}
