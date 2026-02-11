nozomi_setup_private_data(struct nozomi *dc)
{
	void __iomem *offset = dc->base_addr + dc->card_type / 2;
	unsigned int i;

	dc->reg_fcr = (void __iomem *)(offset + R_FCR);
	dc->reg_iir = (void __iomem *)(offset + R_IIR);
	dc->reg_ier = (void __iomem *)(offset + R_IER);
	dc->last_ier = 0;
	dc->flip = 0;

	dc->port[PORT_MDM].token_dl = MDM_DL;
	dc->port[PORT_DIAG].token_dl = DIAG_DL;
	dc->port[PORT_APP1].token_dl = APP1_DL;
	dc->port[PORT_APP2].token_dl = APP2_DL;

	for (i = 0; i < MAX_PORT; i++)
		init_waitqueue_head(&dc->port[i].tty_wait);
}
