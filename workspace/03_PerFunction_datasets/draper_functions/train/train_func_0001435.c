gfarm_sockaddr_to_string(struct sockaddr *addr, char *string, size_t size)
{
	unsigned char *a;
#ifndef HAVE_SNPRINTF
	char s[GFARM_SOCKADDR_STRLEN];

	if (size <= 0)
		return;
#endif
	switch (addr->sa_family) {
	case AF_INET:
		a = (unsigned char *)
		    &((struct sockaddr_in *)addr)->sin_addr.s_addr;
#ifdef HAVE_SNPRINTF
		snprintf(string, size, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
#else
		sprintf(s, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
		strncpy(string, s, size);
		string[size - 1] = '\0';
#endif
		break;
	default:
#ifdef HAVE_SNPRINTF
		snprintf(string, size, "unknown address family %d",
			 addr->sa_family);
#else
		sprintf(s, "unknown address family %d", addr->sa_family);
		strncpy(string, s, size);
		string[size - 1] = '\0';
#endif
		break;
	}
}
