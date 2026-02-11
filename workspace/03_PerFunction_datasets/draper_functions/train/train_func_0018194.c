unwind_lb25_seenophy(unicode_lb_info_t i)
{
	int rc;


	int nolb25_flag=1;

	i->next_handler=next_def;
	i->end_handler=end_def;

	do
	{
		rc=next_def_nolb25(i, i->savedclass, nolb25_flag);

		if (rc)
			return rc;


		nolb25_flag=0;
	} while (i->savedcmcnt--);
	return 0;
}
