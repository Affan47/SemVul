group_member_p(const char *group, const char *user)
{
    struct group *g;
    int i;
    g = getgrnam(group);
    if(g == NULL)
	return GROUP_MISSING;
    if(g->gr_mem[0] == NULL)
	return GROUP_EMPTY;
    for(i = 0; g->gr_mem[i] != NULL; i++)
	if(strcmp(user, g->gr_mem[i]) == 0)
	    return GROUP_MEMBER;
    return GROUP_NOT_MEMBER;
}
