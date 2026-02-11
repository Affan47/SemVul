sisfb_validate_mode(struct sis_video_info *ivideo, int myindex, u32 vbflags)
{
	u16 xres=0, yres, myres;

#ifdef CONFIG_FB_SIS_300
	if(ivideo->sisvga_engine == SIS_300_VGA) {
		if(!(sisbios_mode[myindex].chipset & MD_SIS300))
			return -1 ;
	}
#endif
#ifdef CONFIG_FB_SIS_315
	if(ivideo->sisvga_engine == SIS_315_VGA) {
		if(!(sisbios_mode[myindex].chipset & MD_SIS315))
			return -1;
	}
#endif

	myres = sisbios_mode[myindex].yres;

	switch(vbflags & VB_DISPTYPE_DISP2) {

	case CRT2_LCD:
		xres = ivideo->lcdxres; yres = ivideo->lcdyres;

		if((ivideo->SiS_Pr.SiS_CustomT != CUT_PANEL848) &&
		   (ivideo->SiS_Pr.SiS_CustomT != CUT_PANEL856)) {
			if(sisbios_mode[myindex].xres > xres)
				return -1;
			if(myres > yres)
				return -1;
		}

		if(ivideo->sisfb_fstn) {
			if(sisbios_mode[myindex].xres == 320) {
				if(myres == 240) {
					switch(sisbios_mode[myindex].mode_no[1]) {
						case 0x50: myindex = MODE_FSTN_8;  break;
						case 0x56: myindex = MODE_FSTN_16; break;
						case 0x53: return -1;
					}
				}
			}
		}

		if(SiS_GetModeID_LCD(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
			 	sisbios_mode[myindex].yres, 0, ivideo->sisfb_fstn,
			 	ivideo->SiS_Pr.SiS_CustomT, xres, yres, ivideo->vbflags2) < 0x14) {
			return -1;
		}
		break;

	case CRT2_TV:
		if(SiS_GetModeID_TV(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
				sisbios_mode[myindex].yres, 0, ivideo->vbflags2) < 0x14) {
			return -1;
		}
		break;

	case CRT2_VGA:
		if(SiS_GetModeID_VGA2(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
				sisbios_mode[myindex].yres, 0, ivideo->vbflags2) < 0x14) {
			return -1;
		}
		break;
	}

	return myindex;
}
