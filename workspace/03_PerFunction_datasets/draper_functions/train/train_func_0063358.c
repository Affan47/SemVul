VgaInit(void)
{
    int	i;

    VgaGetPELS(&textPels);


    PortInb(vgaSt1Addr);
    PortOutb(0x00, VGAATTR_A_O);

    for (i = 0; i < VGACRT_CNT; i++) {
	PortOutb(i, vgaCrtAddr);
	regText.crt[i] = PortInb(vgaCrtData);
    }
    for (i = 0; i < VGAATTR_CNT; i++) {
	PortInb(vgaSt1Addr);
	PortOutb(i, VGAATTR_A_O);
	regText.att[i] = PortInb(VGAATTR_DATA);
    }
    for (i = 0; i < VGAGRP_CNT; i++) {
	PortOutb(i, VGAGRP_ADDR);
	regText.gra[i] = PortInb(VGAGRP_DATA);
    }
    for (i = 0; i < VGASEQ_CNT; i++) {
	PortOutb(i, VGASEQ_ADDR);
	regText.seq[i] = PortInb(VGASEQ_DATA);
    }
    regText.mis = PortInb(VGAMISC_IN);

    PortOutb(PortInb(VGAMISC_IN)|0x01, VGAMISC_OUT);
    VgaSetRegisters(&regGraph);


    PortOutw(0x0204, VGAGRP_ADDR);
    memcpy(fontBuff1, gramMem, FONT_SIZE);
#ifdef	USE_ROMFONT
    VgaLoadRomFont(fontBuff1);
#endif
#if defined(MINI_KON) || defined(USE_STATICFONT)
    VgaLoadStaticFont();
#endif

    if (savePlane3 && fontBuff2) {

	PortOutw(0x0304, VGAGRP_ADDR);
	memcpy(fontBuff2, gramMem, FONT_SIZE);
    }
}
