hx509_peer_info_free(hx509_peer_info peer)
{
    if (peer == NULL)
	return;
    if (peer->cert)
	hx509_cert_free(peer->cert);
    free_cms_alg(peer);
    memset(peer, 0, sizeof(*peer));
    free(peer);
}
