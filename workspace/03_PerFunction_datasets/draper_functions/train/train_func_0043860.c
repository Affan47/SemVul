expire_nodes()
{
    std::map<std::string, serviceinfo, std::less<std::string> >::iterator s(servicelist.begin());
    time_t current_time = time(NULL);

    for (; s != servicelist.end(); s++)
    {

	if (s->first != "")
	{
	    servicelist[s->first].expire_nodes(current_time);
	}
    }
}
