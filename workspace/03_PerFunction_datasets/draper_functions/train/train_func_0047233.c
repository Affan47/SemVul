sisfb_set_mode(struct sis_video_info *ivideo, int clrscrn)
{
	unsigned short modeno = ivideo->mode_no;


	modeno |= 0x80;

	SiS_SetReg(SISSR, IND_SIS_PASSWORD, SIS_PASSWORD);

	sisfb_pre_setmode(ivideo);

	if(!SiSSetMode(&ivideo->SiS_Pr, modeno)) {
		printk(KERN_ERR "sisfb: Setting mode[0x%x] failed\n", ivideo->mode_no);
		return -EINVAL;
	}

	SiS_SetReg(SISSR, IND_SIS_PASSWORD, SIS_PASSWORD);

	sisfb_post_setmode(ivideo);

	return 0;
}
