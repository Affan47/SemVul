server_refuse_connection(server_listener sl, network_handle nh)
{
    slistener *l = sl.ptr;

    if (l->print_messages)
	send_message(l->oid, nh, "server_full_msg",
		     "*** Sorry, but the server cannot accept any more"
		     " connections right now.",
		     "*** Please try again later.",
		     0);
    errlog("SERVER FULL: refusing connection on %s from %s\n",
	   l->name, network_connection_name(nh));
}
