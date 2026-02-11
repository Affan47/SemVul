read_link_configuration(LinkFactory::link_construction_plan_t &link_plan, Setting &settings) {
	settings.value("type", link_plan.link_type);
	settings.value("name", link_plan.dev_name);
	settings.value("port", link_plan.port);
	settings.value("baudrate", link_plan.baudrate);
	settings.value("protocol", link_plan.protocol_type);
	settings.value("members", link_plan.groupmember_list);
}
