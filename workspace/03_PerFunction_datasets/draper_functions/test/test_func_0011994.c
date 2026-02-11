agmt_set_schedule_from_entry( Repl_Agmt *ra, const Slapi_Entry *e )
{
	Slapi_Attr	*sattr;
	int			return_value = 0;

	PR_ASSERT(NULL != ra);
	PR_Lock(ra->lock);
	if (ra->stop_in_progress)
	{
		PR_Unlock(ra->lock);
		return return_value;
	}
	PR_Unlock(ra->lock);

	if (slapi_entry_attr_find(e, type_nsds5ReplicaUpdateSchedule, &sattr) != 0)
	{
		sattr = NULL;
	}


	return_value = schedule_set(ra->schedule, sattr);

	if ( 0 == return_value ) {

		prot_notify_agmt_changed(ra->protocol, ra->long_name);
	}

	return return_value;
}
