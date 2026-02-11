setipxname (argv)
    char **argv;
{
    char *dest = ipxcp_wantoptions[0].name;
    char *src  = *argv;
    int  count;
    char ch;

    ipxcp_wantoptions[0].neg_name  = 1;
    ipxcp_allowoptions[0].neg_name = 1;
    memset (dest, '\0', sizeof (ipxcp_wantoptions[0].name));

    count = 0;
    while (*src) {
        ch = *src++;
	if (! isalnum (ch) && ch != '_') {
	    option_error("IPX router name must be alphanumeric or _");
	    return 0;
	}

	if (count >= sizeof (ipxcp_wantoptions[0].name)) {
	    option_error("IPX router name is limited to %d characters",
			 sizeof (ipxcp_wantoptions[0].name) - 1);
	    return 0;
	}

	dest[count++] = toupper (ch);
    }

    return 1;
}
