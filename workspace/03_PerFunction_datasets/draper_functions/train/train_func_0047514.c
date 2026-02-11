wcn36xx_dxe_get_next_bd(struct wcn36xx *wcn, bool is_low)
{
	struct wcn36xx_dxe_ch *ch = is_low ?
		&wcn->dxe_tx_l_ch :
		&wcn->dxe_tx_h_ch;

	return ch->head_blk_ctl->bd_cpu_addr;
}
