hisax_init_pcmcia(void *pcm_iob, int *busy_flag, struct IsdnCard *card)
{
	u_char ids[16];
	int ret = -1;

	cards[nrcards] = *card;
	if (nrcards)
		sprintf(ids, "HiSax%d", nrcards);
	else
		sprintf(ids, "HiSax");
	if (!checkcard(nrcards, ids, busy_flag, THIS_MODULE,
		       hisax_cs_setup_card))
		goto error;

	ret = nrcards;
	nrcards++;
error:
	return ret;
}
