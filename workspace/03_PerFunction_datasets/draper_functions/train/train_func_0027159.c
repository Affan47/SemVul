do_battery_test(void)
{
	char buffer[32];

	if (getval("testtime") == NULL)
		snprintf(buffer, 3, "%s", DEFAULT_BAT_TEST_TIME);
	else {
		snprintf(buffer, 3, "%s", getval("testtime"));


		if (strlen(buffer) < 2) {
			buffer[2] = '\0';
			buffer[1] = buffer[0];
			buffer[0] = '0';
		}
	}
	ser_send(upsfd,"%s%s%s",BAT_TEST_PREFIX,buffer,COMMAND_END);
}
