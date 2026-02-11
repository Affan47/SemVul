message_func (adcli_message_type type,
              const char *message)
{
	const char *prefix = "";

	switch (type) {
	case ADCLI_MESSAGE_INFO:
		prefix = " * ";
		break;
	case ADCLI_MESSAGE_WARNING:
	case ADCLI_MESSAGE_ERROR:
		prefix = " ! ";
		break;
	}

	fprintf (stderr, "%s%s\n", prefix, message);
}
