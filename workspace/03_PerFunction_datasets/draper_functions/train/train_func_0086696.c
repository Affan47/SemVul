sisfb_post_xgi_ddr2(struct sis_video_info *ivideo, u8 regb)
{
	unsigned char *bios = ivideo->bios_abase;
	static const u8 cs158[8] = {
		0x88, 0xaa, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	static const u8 cs160[8] = {
		0x44, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	static const u8 cs168[8] = {
		0x48, 0x78, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	u8 reg;
	u8 v1;
	u8 v2;
	u8 v3;

	SiS_SetReg(SISCR, 0xb0, 0x80);
	SiS_SetReg(SISCR, 0x82, 0x77);
	SiS_SetReg(SISCR, 0x86, 0x00);
	reg = SiS_GetReg(SISCR, 0x86);
	SiS_SetReg(SISCR, 0x86, 0x88);
	reg = SiS_GetReg(SISCR, 0x86);
	v1 = cs168[regb]; v2 = cs160[regb]; v3 = cs158[regb];
	if (ivideo->haveXGIROM) {
		v1 = bios[regb + 0x168];
		v2 = bios[regb + 0x160];
		v3 = bios[regb + 0x158];
	}
	SiS_SetReg(SISCR, 0x86, v1);
	SiS_SetReg(SISCR, 0x82, 0x77);
	SiS_SetReg(SISCR, 0x85, 0x00);
	reg = SiS_GetReg(SISCR, 0x85);
	SiS_SetReg(SISCR, 0x85, 0x88);
	reg = SiS_GetReg(SISCR, 0x85);
	SiS_SetReg(SISCR, 0x85, v2);
	SiS_SetReg(SISCR, 0x82, v3);
	SiS_SetReg(SISCR, 0x98, 0x01);
	SiS_SetReg(SISCR, 0x9a, 0x02);
	if (sisfb_xgi_is21(ivideo))
		sisfb_post_xgi_ddr2_mrs_xg21(ivideo);
	else
		sisfb_post_xgi_ddr2_mrs_default(ivideo, regb);
}
