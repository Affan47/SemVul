mainloop(struct PCP *pcp)
{
	int c;
	struct pcpdtimer inactivity_timeout;
	int my_acl_flags=PCP_ACL_MODIFY|PCP_ACL_CONFLICT|
		PCP_ACL_LIST|PCP_ACL_RETR;

	deleted_eventid=NULL;
	memset(&new_commit, 0, sizeof(new_commit));
	new_commit_times=NULL;
	new_commit_participants=NULL;
	new_commit_participants_buf=NULL;

	termsig=0;

	setsigs();

	inp_ptr=0;
	inp_left=0;
	need_rset=0;

	time(&prev_time);

	pcpdtimer_init(&inactivity_timeout);
	inactivity_timeout.handler=inactive;

	if (proxy_userid)
	{
		struct get_acl ga;

		ga.who=proxy_userid;
		ga.flags=0;
		if (pcp_has_acl(pcp))
		{
			if (pcp_list_acl(pcp, get_acl_callback, &ga) == 0)
			{
				if (ga.flags == 0)
				{
					ga.who="public";
					if (pcp_list_acl(pcp, get_acl_callback,
							 &ga))
						ga.flags=0;
				}
			}
			else ga.flags=0;
		}
		my_acl_flags=ga.flags;
	}

	do
	{
		char *p;

		input_line_len=0;
		pcpdtimer_install(&inactivity_timeout, 30 * 60);

		for (;;)
		{


			c=inputchar(pcp);

			if (termsig || c == '\n')
				break;
			input_buffer[input_line_len++]=c;
		}
		if (termsig)
			break;

		input_buffer[input_line_len]=0;

		for (p=input_buffer; *p; p++)
			if (isspace((int)(unsigned char)*p))
				*p=' ';
		pcpdtimer_triggered(&inactivity_timeout);


	} while (doline(pcp, input_buffer, my_acl_flags) == 0 && !termsig);
	alarm(0);
	free(input_buffer);
	rset(pcp);
}
