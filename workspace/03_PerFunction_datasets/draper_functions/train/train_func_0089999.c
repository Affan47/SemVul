backend_starttls(struct backend *s, struct tls_cmd_t *tls_cmd)
{
#ifndef HAVE_SSL
    return -1;
#else
    int r;
    int *layerp;
    char *auth_id;

    if (tls_cmd) {
	char buf[2048];


	prot_printf(s->out, "%s\r\n", tls_cmd->cmd);
	prot_flush(s->out);


	if (!prot_fgets(buf, sizeof(buf), s->in) ||
	    strncmp(buf, tls_cmd->ok, strlen(tls_cmd->ok)))
	    return -1;
    }

    r = tls_init_clientengine(5, "", "");
    if (r == -1) return -1;


    layerp = (int *) &s->ext_ssf;
    r = tls_start_clienttls(s->in->fd, s->out->fd, layerp, &auth_id,
			    &s->tlsconn, &s->tlssess);
    if (r == -1) return -1;

    if (s->saslconn) {
	r = sasl_setprop(s->saslconn, SASL_SSF_EXTERNAL, &s->ext_ssf);
	if (r == SASL_OK)
	    r = sasl_setprop(s->saslconn, SASL_AUTH_EXTERNAL, auth_id);
	if (auth_id) free(auth_id);
	if (r != SASL_OK) return -1;
    }

    prot_settls(s->in,  s->tlsconn);
    prot_settls(s->out, s->tlsconn);

    return 0;
#endif
}
