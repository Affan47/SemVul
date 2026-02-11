repopulateCombos(void)
{


	EV_Toolbar * pTbar = NULL;
	UT_uint32 ibar = 0;
	do
	{
		pTbar = getToolbar(ibar++);
		if(pTbar)
			pTbar->repopulateStyles();
	}
	while(pTbar);
	return true;
}
