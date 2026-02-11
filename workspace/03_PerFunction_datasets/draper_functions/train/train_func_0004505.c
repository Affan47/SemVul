curl_dir_parse(void *buffer, size_t size, size_t nmemb, void *userp)
{
	regmatch_t regex_matches[3];
	char path[MAXURLLEN], url[MAXURLLEN];
	char errbuf[1024];
	static char *save = NULL;
	char *currentp, *startp, *cp;
	size_t buflen = 0;
	int i;
	curl_dir_state_t *csp = (curl_dir_state_t *)userp;

# ifdef DEBUG
	printf("==> curl_read(buffer=0x%lx, size=%lu, nmemb=%lu, "
	       "userp=0x%lx)\n", buffer, size, nmemb, userp);
	printf("buffer = \"%s\"\n", buffer);
# endif

	if (save != NULL)
	{
		buflen = strlen(save) + (size * nmemb) + 1;
		startp = (char *)malloc(buflen);
		strlcpy(startp, save, buflen);
		strlcat(startp, buffer, buflen);
		currentp = startp;
		free(save);
		save = NULL;
	}
	else
	{
		startp = buffer;
		currentp = buffer;
	}

	while ((i = regexec(&html_link_regexp, currentp,
			    3, regex_matches, 0)) == 0)
	{
		snprintf(path, sizeof(path), "%.*s",
			 regex_matches[1].rm_eo - regex_matches[1].rm_so,
			 currentp + regex_matches[1].rm_so);


		if (strstr(path, "://") == NULL)
		{
			strlcpy(url, csp->cs_dir_url, sizeof(url));


			cp = strrchr(url, '?');
			if (cp != NULL)
				*cp = '\0';


			cp = strrchr(url, '/');
			if (cp != NULL && cp != (url + strlen(url) - 1))
			{
				if (path[0] != '/')
					cp++;
				*cp = '\0';
			}


			strlcat(url, path, sizeof(url));
		}
		else
			strlcpy(url, path, sizeof(url));

# ifdef DEBUG
		printf("\t[%s]\n", url);
# endif

		if ((*(csp->cs_dirfunc))(url, csp->cs_state) == -1)
			return -1;

		currentp += regex_matches[0].rm_eo;
	}
	if (i != REG_NOMATCH)
	{
		regerror(i, &html_link_regexp, errbuf, sizeof(errbuf));
		fprintf(stderr, "  ! regcomp(): %s\n", errbuf);
		return -1;
	}

	currentp = strrchr(startp, '<');
	if (currentp != NULL
	    && strchr(currentp, '>') == NULL)
		save = strdup(currentp);

	if (buflen > 0)
		free(startp);

	return (size * nmemb);
}
