tmodes(incap, outcap, instr, outstr, def_instr, def_outstr, spp)
	char *incap;
	char *outcap;
	char **instr;
	char **outstr;
	char *def_instr;
	char *def_outstr;
	char **spp;
{
	*instr = ltgetstr(incap, spp);
	if (*instr == NULL)
	{

		*instr = def_instr;
		*outstr = def_outstr;
		return;
	}

	*outstr = ltgetstr(outcap, spp);
	if (*outstr == NULL)

		*outstr = ltgetstr("me", spp);
	if (*outstr == NULL)

		*outstr = "";
}
