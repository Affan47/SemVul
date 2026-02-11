get_hostname(void)
{
    int len = 128;
    char *hostname = NULL;
    do {
	len *= 2;
	hostname = sresize(hostname, len, char);
	if ((gethostname(hostname, len) < 0) &&
	    (errno != ENAMETOOLONG)) {
	    sfree(hostname);
	    hostname = NULL;
	    break;
	}
    } while (strlen(hostname) >= len-1);
    return hostname;
}
