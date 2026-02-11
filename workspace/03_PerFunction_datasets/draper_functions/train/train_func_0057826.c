au_del_group(name)
    char_u	*name;
{
    int	    i;

    i = au_find_group(name);
    if (i == AUGROUP_ERROR)
	EMSG2(_("E367: No such group: \"%s\""), name);
    else
    {
	vim_free(AUGROUP_NAME(i));
	AUGROUP_NAME(i) = NULL;
    }
}
