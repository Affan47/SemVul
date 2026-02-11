tomoyo_correct_domain(const unsigned char *domainname)
{
	if (!domainname || !tomoyo_domain_def(domainname))
		return false;
	domainname = strchr(domainname, ' ');
	if (!domainname++)
		return true;
	while (1) {
		const unsigned char *cp = strchr(domainname, ' ');
		if (!cp)
			break;
		if (*domainname != '/' ||
		    !tomoyo_correct_word2(domainname, cp - domainname))
			return false;
		domainname = cp + 1;
	}
	return tomoyo_correct_path(domainname);
}
