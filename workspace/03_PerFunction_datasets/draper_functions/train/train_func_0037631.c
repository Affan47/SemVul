nc_inq_gvarid(int grpid, const char *varname, int *varidp) {


#ifdef USE_NETCDF4
#ifdef UNUSED
    const char *vp = varname;
#endif
    char *vargroup;
    char *relname;
    char *groupname;
    int status;
    if (varname[0] == '\0')
	return NC_ENOTVAR;
    vargroup = strdup(varname);
    if (vargroup == NULL)
	return NC_ENOMEM;
    relname = strrchr(vargroup, NC_GRP_DELIM);
    if (relname != NULL) {
	size_t len;
	*relname++ = '\0';

	if ( (status = nc_inq_grpname_full(grpid, &len, NULL)) != NC_NOERR ) {
	    free(vargroup);
	    return status;
	}
	groupname = (char *)emalloc(len + 1);
	if ( (status = nc_inq_grpname_full(grpid, &len, groupname)) == NC_NOERR ) {
	    if(varname[0] == NC_GRP_DELIM) {
		if( strcmp(groupname, vargroup) == 0)
		    status = nc_inq_varid(grpid, relname, varidp);
		else
		    status = NC_ENOTVAR;
	    } else {
		if(strendswith(groupname, vargroup))
		    status = nc_inq_varid(grpid, relname, varidp);
		else
		    status = NC_ENOTVAR;
	    }
	}
	free(vargroup);
	free(groupname);
	return status;
    }
    free(vargroup);
#endif
    return nc_inq_varid(grpid, varname, varidp);
}
