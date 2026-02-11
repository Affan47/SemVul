auto_apt_conf_switch(char *name)
{
    char *p = auto_apt_conf_var(name, NULL);
    if (p == NULL)
	return 0;
    if (strcasecmp(p, "no") == 0 || strcasecmp(p, "off") == 0)
	return 0;
    return 1;
}
