note_roamer(const netid_t whofrom, struct ua_pal *inmsg, const int inlng)
{
	struct	hhash	*sender, *client;


	if  (inlng != sizeof(struct ua_pal)  ||  !((sender = find_remote(whofrom))  &&  sender->rem.ht_flags & HT_TRUSTED))
		return;

	if  ((client = find_remote(inmsg->uap_netid)))  {


		if  (!(client->rem.ht_flags & HT_ROAMUSER))
			return;
		if  (strcmp(client->dosname, inmsg->uap_wname) == 0)
			return;
		free(client->actname);
		free(client->dosname);
		client->actname = stracpy(inmsg->uap_name);
		client->dosname = stracpy(inmsg->uap_wname);
		if  (tracing & TRACE_SYSOP)
			client_trace_op_name(whofrom, "Note roam user", client->actname);
		client->lastaction = time((time_t *) 0);
	}
	else  {


		if  (!new_roam_name(inmsg->uap_netid, &client, inmsg->uap_wname))
			return;
		client->flags = UAL_OK;
		if  (tracing & TRACE_SYSOP)
			client_trace_op_name(whofrom, "Note new roam user", inmsg->uap_wname);
	}

	tell_sched_roam(inmsg->uap_netid, client->actname);
}
