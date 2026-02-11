create_local_port(unsigned char *service,
				 unsigned char *portname,
				 unsigned char *devname,
				 unsigned char *remnode,
				 bool queued,
				 bool clean,
				 unsigned char *password)
{
    debuglog(("Server::create_local_port: %s\n", devname));


    std::list<LocalPort>::iterator i(portlist.begin());
    for (; i != portlist.end(); i++)
    {
	if (strcmp(i->get_devname().c_str(), (char *)devname) == 0)
	{
	    return 1;
	}
    }

    portlist.push_back(LocalPort(service, portname, devname, remnode, queued, clean, password));


    std::list<LocalPort>::iterator p(portlist.begin());
    for (; p != portlist.end(); p++)
    {
	if (strcmp(p->get_devname().c_str(), (char *)devname) == 0)
	{
	    p->init_port();
	    break;
	}
    }

    return 0;
}
