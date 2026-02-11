unknownprint(void)
{
    char line[80], *cp;
    int width = 27;

    if (vflag)
	snprintf(line, sizeof line, "%s.", "*");
    else
	snprintf(line, sizeof line, "%.*s.", width-9, "*");
    cp = strchr(line, '\0');
    snprintf(cp, line + sizeof line - cp, vflag ? "%s" : "%.8s", "*");
    if (vflag && width < strlen(line))
	width = strlen(line);
    printf(" %-*.*s", width, width, line);
}
