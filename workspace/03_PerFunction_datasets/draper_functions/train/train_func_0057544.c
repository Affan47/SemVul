boot_args(char **args)
{
    int len = 0, a = 0;
    char **pp;
    const char *p;
    char c, *q, *str;

    for (pp = args; *pp; pp++)
	len += strlen(*pp) + 1;

    q = str = alloca(len);
    for (pp = args; *pp; pp++) {
	p = *pp;
	while ((c = *p++))
	    *q++ = c;
	*q++ = ' ';
	a = 1;
    }
    q -= a;
    *q = '\0';

    if (!str[0])
	syslinux_run_default();
    else
	syslinux_run_command(str);
}
