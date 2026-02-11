sisfbcheckvretracecrt1(struct sis_video_info *ivideo)
{
	if(!sisfballowretracecrt1(ivideo))
		return false;

	if (SiS_GetRegByte(SISINPSTAT) & 0x08)
		return true;
	else
		return false;
}
