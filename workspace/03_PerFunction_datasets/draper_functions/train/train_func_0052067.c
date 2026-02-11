filter_domain(char * domain_name)
{
	int domain_fd;
	ssize_t count;
	char get_domain[DOMAINLEN];
	char ch[1];
	int j = 0;
	domain_fd = open(FILTER_DOMAIN_LIST, O_RDONLY);
	if(domain_fd < 0)
	{
		my_err("Open Domain Filter", __LINE__);
		return 0;
	}
	while((count = read(domain_fd, ch, 1)) == 1)
	{
		if(*ch == '\n')
		{
			get_domain[j] = '\0';
			if(strcmp(get_domain, domain_name) == 0) return 1;
			j = 0;
			sleep(1);
		}
		else
		{
			get_domain[j++] = *ch;
		}
	}
	return 0;
}
