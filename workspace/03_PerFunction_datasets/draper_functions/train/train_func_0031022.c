unblock_handler(void *closure)
{
    TCP_Client *client = (TCP_Client *) closure;


    Scanner *scanner = client->my_scanner;
    if (scanner)
    {	if (scanner->done())
	    client->my_scanner = NULL;
	else
	    return;
    }


    Interest *ip;
    while (client->ready_for_events() && (ip = client->to_be_scanned.first()))
    {   client->to_be_scanned.remove(ip);
	ip->scan();
    }


    if (client->ready_for_events())
	client->conn.ready_for_input(true);
}
