pg_results_liveunprop(void *userdata, const char *uri,
		       const ne_prop_result_set *rset)
{
	int i;
	const ne_status *status;

	if (STATUS(207))
		t_warning("PROPPATCH of live unprotected property got %d response, not 207", GETSTATUS);
    	else
	{
		for (i=0;i<numlp_unprotect;i++)
		{
			status = ne_propset_status(rset, &live_prop_unprotect[i]);
			if (status->code != 200)
			t_warning("The status for setting property %s was %d and not 200 as expected",
				live_prop_unprotect[i].name, status->code);
		}
	}
}
