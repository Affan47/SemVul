krb5_init_context(krb5_context *context)
{
    static heim_base_once_t init_context = HEIM_BASE_ONCE_INIT;
    krb5_context p;
    krb5_error_code ret;
    char **files;
    uint8_t rnd;

    *context = NULL;


    ret = krb5_generate_random(&rnd, sizeof(rnd));
    if (ret)
	return ret;

    p = calloc(1, sizeof(*p));
    if(!p)
	return ENOMEM;

    p->mutex = malloc(sizeof(HEIMDAL_MUTEX));
    if (p->mutex == NULL) {
	free(p);
	return ENOMEM;
    }
    HEIMDAL_MUTEX_init(p->mutex);

    p->flags |= KRB5_CTX_F_HOMEDIR_ACCESS;

    ret = krb5_get_default_config_files(&files);
    if(ret)
	goto out;
    ret = krb5_set_config_files(p, files);
    krb5_free_config_files(files);
    if(ret)
	goto out;


    heim_base_once_f(&init_context, p, init_context_once);


    krb5_init_ets(p);
    cc_ops_register(p);
    kt_ops_register(p);

#ifdef PKINIT
    ret = hx509_context_init(&p->hx509ctx);
    if (ret)
	goto out;
#endif
    if (rk_SOCK_INIT())
	p->flags |= KRB5_CTX_F_SOCKETS_INITIALIZED;

out:
    if(ret) {
	krb5_free_context(p);
	p = NULL;
    }
    *context = p;
    return ret;
}
