process(const message &m)
{
	if (verbose)
		cerr << "Message " << m;
	if (m.gettype()=="add_plugin")
		add_plugin(m);
	else if (m.gettype()=="register")
		add_registration(m);
	else if (m.gettype()=="unregister")
		remove_registration(m);
	else if (m.type=="done")
		remove_plugin(m);
	else if (m.type=="target")
		target_plugin(m);
	else if (m.type=="core_quit")
		initiate_shutdown();
	else
		to_plugin(m);
}
