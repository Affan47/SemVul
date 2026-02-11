init_digest_types(ErlNifEnv* env)
{
    struct digest_type_t* p = digest_types;

    for (p = digest_types; p->type_str; p++) {
	p->type_atom = enif_make_atom(env, p->type_str);
    }

}
