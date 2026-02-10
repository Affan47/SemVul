card_open(struct sstate *ss, char *dev)
{
	struct wif *wi = wi_open(dev);

	if (!wi)
		err(1, "wi_open()");
	ss->ss_wi = wi;
}
