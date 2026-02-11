jpeg_start (struct zoran *zr)
{
	int reg;

	zr->frame_num = 0;


	btwrite(ZR36057_JPC_P_Reset, ZR36057_JPC);

	btand(~ZR36057_MCTCR_CFlush, ZR36057_MCTCR);

	btor(ZR36057_JPC_CodTrnsEn, ZR36057_JPC);


	btwrite(IRQ_MASK, ZR36057_ISR);

	btwrite(zr->card.jpeg_int |
			ZR36057_ICR_JPEGRepIRQ |
			ZR36057_ICR_IntPinEn,
		ZR36057_ICR);

	set_frame(zr, 0);


	reg = (zr->card.gpcs[1] << ZR36057_JCGI_JPEGuestID) |
	       (0 << ZR36057_JCGI_JPEGuestReg);
	btwrite(reg, ZR36057_JCGI);

	if (zr->card.video_vfe == CODEC_TYPE_ZR36016 &&
	    zr->card.video_codec == CODEC_TYPE_ZR36050) {

		if (zr->vfe)
			zr36016_write(zr->vfe, 0, 1);


		post_office_write(zr, 0, 0, 0);
	}


	btor(ZR36057_JPC_Active, ZR36057_JPC);


	btor(ZR36057_JMC_Go_en, ZR36057_JMC);
	udelay(30);

	set_frame(zr, 1);

	dprintk(3, KERN_DEBUG "%s: jpeg_start\n", ZR_DEVNAME(zr));
}
