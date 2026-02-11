imm_connect(imm_struct *dev, int flag)
{
	unsigned short ppb = dev->base;

	imm_cpp(ppb, 0xe0);
	imm_cpp(ppb, 0x30);

	if ((dev->mode == IMM_EPP_8) ||
	    (dev->mode == IMM_EPP_16) ||
	    (dev->mode == IMM_EPP_32))
		return imm_cpp(ppb, 0x28);
	return imm_cpp(ppb, 0xe0);
}
