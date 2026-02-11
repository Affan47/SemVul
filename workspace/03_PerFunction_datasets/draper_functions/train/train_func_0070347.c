MGD77_Write_Data_Record_m77 (struct MGD77_CONTROL *F, struct MGD77_DATA_RECORD *MGD77Record)
{
	int nwords = 0, nvalues = 0, i;
	char buffer[BUFSIZ];

	for (i = 0; i < MGD77_N_DATA_FIELDS; i++) {
		if (i == 1) sprintf (buffer, mgd77defs[24].printMGD77, MGD77Record->word[nwords++]);
		else if (i == 24 || i == 25) sprintf (buffer, mgd77defs[i+1].printMGD77, MGD77Record->word[nwords++]);
		else {
			if (GMT_is_dnan (MGD77Record->number[nvalues]))	sprintf (buffer, "%s", mgd77defs[nvalues].not_given);
			else sprintf (buffer, mgd77defs[nvalues].printMGD77, irint (MGD77Record->number[nvalues]*mgd77defs[nvalues].factor));
			nvalues++;
		}
		GMT_fputs (buffer, F->fp);


	}
	GMT_fputs ("\n", F->fp);
	return (MGD77_NO_ERROR);
}
