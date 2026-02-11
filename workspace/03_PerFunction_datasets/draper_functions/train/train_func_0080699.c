send_to_client(int entry, int ack_remote)
{
    int i;
    int found = FALSE;

    for (i=0; i<MAX_CONNECTIONS; i++)
    {

	if (fdarray[i].type != INACTIVE &&
	    strcmp(fdarray[i].local_user, fdarray[entry].local_user) == 0 &&
	    fdarray[i].type != fdarray[entry].type)
	{
	    char msghead[2];
	    int  decnet_fd, unix_fd;


	    if (fdarray[i].type == DECNET)
	    {
		decnet_fd = i;
		unix_fd   = entry;
	    }
	    else
	    {
		decnet_fd = entry;
		unix_fd   = i;
	    }

	    msghead[0] = strlen(fdarray[decnet_fd].remote_user)+1;
	    msghead[1] = ack_remote;

	    write(fdarray[unix_fd].fd, msghead, 2);
	    write(fdarray[unix_fd].fd, fdarray[decnet_fd].remote_user, msghead[0]);
	    send_fd(fdarray[decnet_fd].fd, fdarray[unix_fd].fd);

	    remove_entry(decnet_fd);
	    found = TRUE;
	}
    }
    return found;
}
