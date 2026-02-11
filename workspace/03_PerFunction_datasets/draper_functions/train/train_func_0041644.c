to_plugin(message m)
{
	if (message_registrations.count(m.gettype())==0)
	{

		if (verbose)
			cerr << " was not registered" << endl;
		return;
	}
	auto plugin=message_registrations[m.gettype()].get(m.getpriority());
	if (plugin.second=="")
	{
		if (verbose)
			cerr << " has no more registered plugins" << endl;
		return;
	}
	if (out_pipes.count(plugin.second)==0)
	{

		if (verbose)
			cerr << " is registered to the non-existent plugin " << plugin.second << endl;
		return;
	}

	out_pipes[plugin.second].write(m.change_priority(plugin.first));
	if (verbose)
		cerr << " was sent to " << plugin.second << " as " << m << endl;
}
