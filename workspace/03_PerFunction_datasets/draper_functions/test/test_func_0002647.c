pgresults_invalid_sem(void *userdata, const char *uri,
		       const ne_prop_result_set *rset)
{
	const ne_status *status;

	if (STATUS(207))
		t_warning("PROPPATCH of property got %d response, not 207",
		  	 GETSTATUS);
    	else
	{


		status = ne_propset_status(rset, &live_prop_unprotect[0]);
		if (status->code != 409)
		t_warning("The status for setting property %s was %d and not 409 as expected",
			live_prop_unprotect[0].name, status->code);
	}
}
