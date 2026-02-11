ph_command(struct isac_hw *isac, u8 command)
{
	pr_debug("%s: ph_command %x\n", isac->name, command);
	if (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_CIX0, (command << 4) | 0xE);
	else
		WriteISAC(isac, ISAC_CIX0, (command << 2) | 3);
}
