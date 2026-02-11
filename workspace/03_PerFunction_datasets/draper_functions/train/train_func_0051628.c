_sanitise_message(char *message)
{
	const char *sanitised_message = message ?: "";


	if (message && !strncasecmp(message, "key set", 7))
		sanitised_message = "key set";

	return sanitised_message;
}
