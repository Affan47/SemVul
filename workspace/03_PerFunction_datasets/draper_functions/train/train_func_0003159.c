ssl_sock_get_remote_common_name(struct connection *conn, struct chunk *dest)
{
	X509 *crt = NULL;
	X509_NAME *name;
	const char find_cn[] = "CN";
	const struct chunk find_cn_chunk = {
		.str = (char *)&find_cn,
		.len = sizeof(find_cn)-1
	};
	int result = -1;

	if (!ssl_sock_is_ssl(conn))
		goto out;


	crt = SSL_get_peer_certificate(conn->xprt_ctx);
	if (!crt)
		goto out;

	name = X509_get_subject_name(crt);
	if (!name)
		goto out;

	result = ssl_sock_get_dn_entry(name, &find_cn_chunk, 1, dest);
out:
	if (crt)
		X509_free(crt);

	return result;
}
