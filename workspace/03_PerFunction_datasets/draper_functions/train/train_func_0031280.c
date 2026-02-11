sisfb_set_pitch(struct sis_video_info *ivideo)
{
	bool isslavemode = false;
	unsigned short HDisplay1 = ivideo->scrnpitchCRT1 >> 3;
	unsigned short HDisplay2 = ivideo->video_linelength >> 3;

	if(sisfb_bridgeisslave(ivideo)) isslavemode = true;


	if((ivideo->currentvbflags & VB_DISPTYPE_DISP1) || (isslavemode)) {
		SiS_SetReg(SISCR, 0x13, (HDisplay1 & 0xFF));
		SiS_SetRegANDOR(SISSR, 0x0E, 0xF0, (HDisplay1 >> 8));
	}


	if((ivideo->currentvbflags & VB_DISPTYPE_DISP2) && (!isslavemode)) {
		SiS_SetRegOR(SISPART1, ivideo->CRT2_write_enable, 0x01);
		SiS_SetReg(SISPART1, 0x07, (HDisplay2 & 0xFF));
		SiS_SetRegANDOR(SISPART1, 0x09, 0xF0, (HDisplay2 >> 8));
	}
}
