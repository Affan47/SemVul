ICDrenumberactive(void)
{
    int	i;
    NEWSGROUP	*ngp;

    for (i = nGroups, ngp = Groups; --i >= 0; ngp++)
	if (!NGrenumber(ngp))
	    return false;
    if (i < 0)
	ICDwrite();
    return true;
}
