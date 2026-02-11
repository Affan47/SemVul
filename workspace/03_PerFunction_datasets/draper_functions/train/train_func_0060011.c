config_find_keyword(ConfigTable *Conf, ConfigArgs *c) {
	int i;

	for(i = 0; Conf[i].name; i++)
		if( (Conf[i].length && (!strncasecmp(c->argv[0], Conf[i].name, Conf[i].length))) ||
			(!strcasecmp(c->argv[0], Conf[i].name)) ) break;
	if ( !Conf[i].name ) return NULL;
	return Conf+i;
}
