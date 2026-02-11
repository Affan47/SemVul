send_solicit_messages(int sig)
{
    static unsigned int counter = 0;
    static unsigned int last_list_size = 0;

    if (alarm_mode == 0)
    {
	counter = 0;
	alarm_mode = 1;
	debuglog(("set alarm_mode to 1\n"));

	if (!known_slave_nodes.empty())
	{
	    std::string known_node = known_slave_nodes.front();
	    known_slave_nodes.pop_front();
	    slave_nodes.push_back(known_node);
	    debuglog(("known(%d) => slave(%d) : %s\n", known_slave_nodes.size(),
		       slave_nodes.size(), known_node.c_str()));
	    if (slave_nodes.size() == 1)
	    {
		alarm_mode = 0;
		debuglog(("set alarm_mode to 0 - one slave\n"));
		send_enq(slave_nodes.front().c_str());

		return;
	    }
	}
    }
    else
    {
	if (slave_nodes.size() < last_list_size)
	{
	    counter -= last_list_size - slave_nodes.size();
	}
    }

    if (slave_nodes.size() > counter && !slave_nodes.empty())
    {
	std::string node_name = slave_nodes.front();
	slave_nodes.pop_front();
	slave_nodes.push_back(node_name);

	send_enq(node_name.c_str());

	alarm(1);
	counter++;
	last_list_size = slave_nodes.size();
    }
    else
    {
	alarm_mode = 0;


	alarm(counter >= multicast_timer ? 1 : multicast_timer - counter);
	debuglog(("set alarm_mode to 0, timer %d\n", counter >= multicast_timer ? 1 : multicast_timer - counter));
    }
}
