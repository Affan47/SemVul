get_rsa_private_key(ErlNifEnv* env, ERL_NIF_TERM key, RSA *rsa)
{

    ERL_NIF_TERM head, tail;

    if (!enif_get_list_cell(env, key, &head, &tail)
	|| !get_bn_from_bin(env, head, &rsa->e)
	|| !enif_get_list_cell(env, tail, &head, &tail)
	|| !get_bn_from_bin(env, head, &rsa->n)
	|| !enif_get_list_cell(env, tail, &head, &tail)
	|| !get_bn_from_bin(env, head, &rsa->d)
	|| (!enif_is_empty_list(env, tail) &&
	    (!enif_get_list_cell(env, tail, &head, &tail)
	     || !get_bn_from_bin(env, head, &rsa->p)
	     || !enif_get_list_cell(env, tail, &head, &tail)
	     || !get_bn_from_bin(env, head, &rsa->q)
	     || !enif_get_list_cell(env, tail, &head, &tail)
	     || !get_bn_from_bin(env, head, &rsa->dmp1)
	     || !enif_get_list_cell(env, tail, &head, &tail)
	     || !get_bn_from_bin(env, head, &rsa->dmq1)
	     || !enif_get_list_cell(env, tail, &head, &tail)
	     || !get_bn_from_bin(env, head, &rsa->iqmp)
	     || !enif_is_empty_list(env, tail)))) {
	return 0;
    }
    return 1;
}
