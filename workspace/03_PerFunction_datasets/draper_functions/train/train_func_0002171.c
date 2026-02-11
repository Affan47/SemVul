ex_fold(eap)
    exarg_T	*eap;
{
    if (foldManualAllowed(TRUE))
	foldCreate(eap->line1, eap->line2);
}
