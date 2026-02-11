tradspool_ctl(PROBETYPE type, TOKEN *token, void *value) {
    struct artngnum *ann;
    unsigned long ngnum;
    unsigned long artnum;
    char *ng, *p;

    switch (type) {
    case SMARTNGNUM:
	if ((ann = (struct artngnum *)value) == NULL)
	    return false;
	CheckNeedReloadDB(false);
	memcpy(&ngnum, &token->token[0], sizeof(ngnum));
	memcpy(&artnum, &token->token[sizeof(ngnum)], sizeof(artnum));
	artnum = ntohl(artnum);
	ngnum = ntohl(ngnum);
	ng = FindNGByNum(ngnum);
	if (ng == NULL) {
	    CheckNeedReloadDB(true);
	    ng = FindNGByNum(ngnum);
	    if (ng == NULL)
		return false;
	}
	ann->groupname = xstrdup(ng);
        for (p = ann->groupname; *p != 0; p++)
            if (*p == '/')
                *p = '.';
	ann->artnum = (ARTNUM)artnum;
	return true;
    default:
	return false;
    }
}
