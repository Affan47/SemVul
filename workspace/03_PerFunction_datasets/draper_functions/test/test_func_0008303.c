globus_l_gass_server_ez_tilde_expand(unsigned long options,
			     char *inpath,
			     char **outpath)
{
#ifndef TARGET_ARCH_WIN32


    if(strlen(inpath) >= 2U)
    {
	if (inpath[1] == '.' && inpath[2] == '/')
	{
	    inpath += 3;
	    goto notilde;
	}
    }


    return globus_tilde_expand(options,
				   GLOBUS_TRUE,
				   inpath,
				   outpath);
#endif

notilde:
    *outpath = globus_malloc(strlen(inpath)+1);
    strcpy(*outpath, inpath);
    return GLOBUS_SUCCESS;
}
