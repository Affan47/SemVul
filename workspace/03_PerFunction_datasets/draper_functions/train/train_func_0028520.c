get_supported_protocols(char ***sup_proto)
{
#ifndef _WIN32
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
	char *last = NULL;
#endif
#endif
	int nb_supported_protocols = 0;
	char *p;
	char *protocols;
	char *sav_protocols;
	char **supported_protocols;

	if ((protocols = getconfent ("DPM", "PROTOCOLS", 1))) {
		if ((sav_protocols = strdup (protocols)) == NULL)
			return (-1);
		p = strtok (protocols, " \t");
		while (p) {
			nb_supported_protocols++;
			p = strtok (NULL, " \t");
		}
		if ((supported_protocols =
		    malloc ((nb_supported_protocols + 1) * sizeof(char *))) == NULL) {
			free (sav_protocols);
			return (-1);
		}
		nb_supported_protocols = 0;
		p = strtok (sav_protocols, " \t");
		while (p) {
			supported_protocols[nb_supported_protocols++] = p;
			p = strtok (NULL, " \t");
		}
		supported_protocols[nb_supported_protocols] = NULL;
	} else {
		supported_protocols = default_protocols;
		while (supported_protocols[nb_supported_protocols])
			nb_supported_protocols++;
	}
	*sup_proto = supported_protocols;
	return (nb_supported_protocols);
}
