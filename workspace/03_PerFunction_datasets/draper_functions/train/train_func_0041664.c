smp_fetch_ssl_fc_cipher(struct proxy *px, struct session *l4, void *l7, unsigned int opt,
                        const struct arg *args, struct sample *smp, const char *kw)
{
	int back_conn = (kw[4] == 'b') ? 1 : 0;
	struct connection *conn;

	smp->flags = 0;

	if (!l4)
		return 0;

	conn = objt_conn(l4->si[back_conn].end);
	if (!conn || !conn->xprt_ctx || conn->xprt != &ssl_sock)
		return 0;

	smp->data.str.str = (char *)SSL_get_cipher_name(conn->xprt_ctx);
	if (!smp->data.str.str)
		return 0;

	smp->type = SMP_T_STR;
	smp->flags |= SMP_F_CONST;
	smp->data.str.len = strlen(smp->data.str.str);

	return 1;
}
