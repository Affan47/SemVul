val_stuff(type, v, ii, val)
     nc_type type;
     void *v;
     int ii;
     long val;
{
    static char pname[] = "val_stuff";
#ifdef WRONG_for_PGCC

    union gp {
	char cp[1];
	short sp[1];
	nclong lp[1];
	float fp[1];
	double dp[1];
    } *gp;

    gp = (union gp *) v;
    switch (type) {
    case NC_BYTE:
    case NC_CHAR:
	gp->cp[ii] = (char) val;
	break;
    case NC_SHORT:
        gp->sp[ii] = (short)val;
	break;
    case NC_LONG:
	gp->lp[ii] = (nclong)val;
	break;
    case NC_FLOAT:
        gp->fp[ii] = (float)val;
	break;
    case NC_DOUBLE:
	gp->dp[ii] = val;
	break;
    default:
	error("%s: bad type, test program error", pname);
#endif
    switch (type) {
    case NC_BYTE:
    case NC_CHAR:
	((char *)v)[ii] = (char) val;
	break;
    case NC_SHORT:
        ((short *)v)[ii] = (short)val;
	break;
    case NC_LONG:
	((nclong *)v)[ii] = (nclong)val;
	break;
    case NC_FLOAT:
        ((float *)v)[ii] = (float)val;
	break;
    case NC_DOUBLE:
	((double *)v)[ii] = (double)val;
	break;
    default:
	error("%s: bad type, test program error", pname);
    }
}
