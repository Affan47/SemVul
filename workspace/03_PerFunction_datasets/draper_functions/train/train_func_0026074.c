del_service(int argc, char *argv[])
{
    char name[255] = {'\0'};
    signed char opt;
    bool got_service = false;
    bool got_port = false;
    opterr = 0;

    while ((opt=getopt(argc,argv,"a:p:")) != EOF)
    {
	switch(opt)
	{
	case 'a':
	    got_service = true;
	    strcpy(name, optarg);
	    make_upper(name);
	    break;

	case 'p':
	    got_port = true;
	    strcpy(name, optarg);
	    break;

	default:
	    fprintf(stderr, "No more service switches defined yet\n");
	    exit(2);
	}
    }

    if ((got_port && got_service) ||
	(!got_port && !got_service))
    {
	fprintf(stderr, "Either -a or -p can be specified but not both\n");
	return;
    }


    if (!open_socket(false)) return;

    char message[520];
    int ptr = 0;
    add_string((unsigned char*)message, &ptr, (unsigned char*)name);
    if (got_service)
	send_msg(latcp_socket, LATCP_REMSERVICE, message, ptr);
    else
	send_msg(latcp_socket, LATCP_REMPORT, message, ptr);

    unsigned char *result = NULL;
    int len;
    int cmd;
    exit(read_reply(latcp_socket, cmd, result, len));
}
