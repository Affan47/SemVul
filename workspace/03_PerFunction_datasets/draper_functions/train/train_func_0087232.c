server_redirect_event(IRC_SERVER_REC *server, const char *command,
			   int count, const char *arg, int remote,
			   const char *failure_signal, ...)
{
	GSList *signals;
        const char *event, *signal;
	va_list va;

	va_start(va, failure_signal);
	signals = NULL;
	while ((event = va_arg(va, const char *)) != NULL) {
		signal = va_arg(va, const char *);
		if (signal == NULL) {
			g_warning("server_redirect_event(%s): "
				  "signal not specified for event", command);
			break;
		}

		signals = g_slist_append(signals, g_strdup(event));
		signals = g_slist_append(signals, g_strdup(signal));
	}

	va_end(va);

	server_redirect_event_list(server, command, count, arg, remote,
				   failure_signal, signals);
}
