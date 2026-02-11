do_if (void)
{	header *cond;
	int flag;
	if (!udfon)
	{	output("If only allowed in functions!\n"); error=111; return;
	}
	another : cond=scan(); if (error) return;
	flag=ctest(cond); if (error) return;
	if (!flag)
		if (scan_else()) goto another;
}
