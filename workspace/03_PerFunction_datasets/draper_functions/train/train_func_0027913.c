voice_set_compression(short c)
{
	char command[64];

	if ((c >= 2) && (c <= 6) && (c != 5))
	{
		printstring(command, "AT+VSM=%d+VLS=2", c);

		log(L_DEBUG, "Setting voice compression \"%s\"...\n", compressions[c]);

		return(modem_command(command, "OK|VCON"));
	}

	log(L_FATAL, "Unknown compression %d - can't set.\n", c);

	returnerror();
}
