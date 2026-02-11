freeinclist()
{
	if (!incdirs)
		return;
	while(nincdirs>0) {
		free(incdirs[--nincdirs]);
		free(incnames[nincdirs]);
	}
	free(incdirs);
	free(incnames);
}
