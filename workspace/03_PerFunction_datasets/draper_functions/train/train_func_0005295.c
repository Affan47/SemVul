find_ptr_by_name(const char **namep, struct ptr_with_slot *rptr)
{
	const	char	*name = *namep;
	const	char	*colp = strchr(name, ':');
	int	pncnt = 0, ret;
	netid_t	nid = dest_hostid;
	char	pn[PTRNAMESIZE+1];

	if  (colp)  {
		char	hostn[HOSTNSIZE+1];
		if  (colp - name > HOSTNSIZE)
			return  0;
		strncpy(hostn, name, colp - name);
		hostn[colp - name] = '\0';
		if  ((nid = my_look_hostname(hostn)) == 0)
			return  0;
		name = colp + 1;
	}

	while  (isalnum(*name)  ||  *name == '_')
		if  (pncnt < PTRNAMESIZE)
			pn[pncnt++] = *name++;
	pn[pncnt] = '\0';

	if  ((ret = gspool_ptrfind(gspool_fd, GSPOOL_FLAG_IGNORESEQ, pn, nid, &rptr->slot, &rptr->ptr)) < 0)  {
		if  (ret != GSPOOL_UNKNOWN_PTR)  {
			html_disperror(26100 + ret);
			exit(E_NETERR);
		}
		return  0;
	}
	return  1;
}
