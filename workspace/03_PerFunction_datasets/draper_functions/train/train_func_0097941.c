cleanup_children(void)
#else
void
cleanup_children()
#endif
{
	int i;
	struct client_command cc;
	bzero(&cc,sizeof(struct client_command));
	cc.c_command = R_DEATH;
	for(i=0;i<num_child;i++)
	{
		cc.c_client_number = (int)i;

		if(child_idents[i].state == C_STATE_ZERO)
			;

		if(child_idents[i].state == C_STATE_WAIT_WHO)
		{
			if(mdebug)
				printf("Master sending signaled death to child !!\n");
			master_send(master_send_sockets[i],child_idents[i].child_name, &cc,sizeof(struct client_command));
		}

		if(child_idents[i].state == C_STATE_WAIT_BARRIER)
		{
			if(mdebug)
				printf("Master sending signaled death to child !!\n");
			master_send(master_send_sockets[i],child_idents[i].child_name, &cc,sizeof(struct client_command));
			if(mdebug)
				printf("Master sending signaled death to child async !!\n");
			master_send(master_send_async_sockets[i],child_idents[i].child_name, &cc,sizeof(struct client_command));
		}

	}
}
