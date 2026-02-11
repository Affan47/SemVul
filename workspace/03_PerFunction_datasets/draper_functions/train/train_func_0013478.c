show_full_details(char *dirname, dap_connection &conn)
{
    dap_message *m;
    dap_name_message       *vol_name_msg = NULL;
    dap_name_message       *dir_name_msg = NULL;
    dap_name_message       *name_msg     = NULL;
    dap_protect_message    *protect_msg  = NULL;
    dap_date_message       *date_msg     = NULL;
    dap_attrib_message     *attrib_msg   = NULL;
    bool                    name_pending = false;

    printf("\n");


    while ( ((m=dap_message::read_message(conn, true) )) )
    {
	switch (m->get_type())
	{
	    case dap_message::NAME:
		name_msg = (dap_name_message *)m;
		switch (name_msg->get_nametype())
		{
		case dap_name_message::VOLUME:
		    vol_name_msg = name_msg;
		    break;
		case dap_name_message::DIRECTORY:
		    dir_name_msg = name_msg;
		    printf("Directory %s%s\n\n",
			   vol_name_msg->get_namespec(),
			   dir_name_msg->get_namespec());
		    break;
		case dap_name_message::FILENAME:
		    name_pending = true;
		}
		break;

	    case dap_message::ATTRIB:
		attrib_msg = (dap_attrib_message *)m;
		break;

	    case dap_message::DATE:
		date_msg = (dap_date_message *)m;
		break;

	    case dap_message::PROTECT:
		protect_msg = (dap_protect_message *)m;
		break;

	    case dap_message::STATUS:
	    {

		dap_status_message *sm = (dap_status_message *)m;
		if (sm->get_code() == 0x4030)
		{
		    printf("%s  File current locked by another user\n\n",
			   name_msg->get_namespec());

		    dap_contran_message cm;
		    cm.set_confunc(dap_contran_message::SKIP);
		    if (!cm.write(conn))
		    {
			fprintf(stderr, "Error sending skip: %s\n", conn.get_error());
			return false;
		    }
		}
		else
		{
		    printf("Error opening %s: %s\n", dirname,
			   sm->get_message());
		    return false;
		}
		name_pending = false;
	    }
	    break;

	    case dap_message::ACK:
		if (name_pending)
		{
		    name_pending = false;
		    print_long(name_msg, attrib_msg, date_msg, protect_msg);

		    delete name_msg;
		    delete protect_msg;
		    delete attrib_msg;
		    delete date_msg;
		}
		break;

	    case dap_message::ACCOMP:
		goto full_flush;
	}
    }

 full_flush:
    if (name_pending)
    {
	print_long(name_msg, attrib_msg, date_msg, protect_msg);

	delete name_msg;
	delete protect_msg;
	delete attrib_msg;
	delete date_msg;
    }
    return true;
}
