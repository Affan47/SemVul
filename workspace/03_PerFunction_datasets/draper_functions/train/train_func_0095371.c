need_connect(struct network *n)
{
	if (n->n_crypto == CRYPTO_WPA)
		return 0;

	switch (n->n_astate) {
	case ASTATE_READY:
	case ASTATE_WEP_PRGA_GET:
	case ASTATE_WEP_FLOOD:
		return 1;

	default:
		return 0;
	}
}
