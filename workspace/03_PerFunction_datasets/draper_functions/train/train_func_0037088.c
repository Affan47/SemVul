config_sect_find(char *snam)
{
	SECTION *sect;
	char    *wild;


	for(sect = sechead; sect; sect = sect->next) {
		if(sect->name && (wild = strchr(sect->name, '*'))) {
#if defined(COMPILE_DEBUG)
			debug(3, "config_sect_find: wildcard-sect='%.*s*'\n",
				  wild - sect->name, sect->name);
#endif
			if (misc_strncaseequ(sect->name, snam,
			                     wild - sect->name))
				break;
		} else {
			if (misc_strcaseequ(sect->name, snam))
				break;
		}
	}
	return sect;
}
