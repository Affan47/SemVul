isprocNorm(char *s)
{
    pname[0] = '\0';
    if ((!l_toplex || blklevel == 0)
	    && expmatch(s, l_prcbeg, (char **) NULL, pname) != NULL
	    && expmatch(s, l_noproc, (char **) NULL, (char *) NULL) == NULL)
    {
	procedures_pending++;
	blklevel++;
	return TRUE;
    }
    return FALSE;
}
