pp_agents_starter_get_server_instance_dir(PP_AgentsStarter *as) {
	Passenger::AgentsStarter *agentsStarter = (Passenger::AgentsStarter *) as;
	return agentsStarter->getServerInstanceDir()->getPath().c_str();
}
