_ml_P_ProcEnv_getgroups (ml_state_t *msp, ml_val_t arg)
{
    gid		gidset[NGROUPS_MAX];
    int		ngrps;
    ml_val_t	p;

    ngrps = getgroups (NGROUPS_MAX, gidset);

    if (ngrps == -1) {
	gid      *gp;


	if (errno != EINVAL)
	    return RAISE_SYSERR(msp, -1);


	ngrps = getgroups (0, gidset);
	gp = (gid *)MALLOC(ngrps * (sizeof (gid)));
	if (gp == 0) {
	    errno = ENOMEM;
	    return RAISE_SYSERR(msp, -1);
	}

	ngrps = getgroups (ngrps, gp);

	if (ngrps == -1)
	    p = RAISE_SYSERR(msp, -1);
	else
	    p = mkList (msp, ngrps, gp);

	FREE ((void *)gp);
    }
    else
	p = mkList (msp, ngrps, gidset);

    return p;

}
