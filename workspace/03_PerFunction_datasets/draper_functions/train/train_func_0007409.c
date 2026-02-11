reload_rules_web(int fd, const char* cmd)
{
	ios_detach_global_handler();
	if(reload_rules(sensor) < 0)
		printf("Web server generated bad rules.xml file");
	else
		ios_attach_global_handler(process_data);
	return 1;
}
