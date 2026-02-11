nvararg(void)
{
	if (FP && FP->vararg)
		return BP - PP;
	else
		return 0;
}
