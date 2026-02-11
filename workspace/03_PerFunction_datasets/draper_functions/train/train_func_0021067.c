gf_rtp_reset_buffers(GF_RTPChannel *ch)
{
	if (ch->rtp) gf_sk_reset(ch->rtp);
	if (ch->rtcp) gf_sk_reset(ch->rtcp);
	if (ch->po) gf_rtp_reorderer_reset(ch->po);


	ch->first_SR = 1;
}
