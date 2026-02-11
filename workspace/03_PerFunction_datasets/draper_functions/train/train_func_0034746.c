scan_spool_dir(grp)
    struct grp *grp;
{
    long oldhi;
    long oldlow;
    long newhi;
    long newlow;
    BOOL found;
    char *hi;
    char *low;


    if (grp == NULL) {
	fprintf(stderr,
	    "%s: internal error #14, grp is NULL\n", program);
	exit(53);
    }


    oldhi = atol(grp->outhi);
    oldlow = atol(grp->outlow);
    found = HiLowWater(grp->name, &newhi, &newlow, (long)-1, (long)-1);
    if (D_SUMMARY) {
	fprintf(stderr,
	    "%s: new: %s, found %d, old hi/low: %ld %ld, new hi/low: %ld %ld\n",
	    program, grp->name, found, oldhi, oldlow, newhi, newlow);
    }
    if (!found) {


	if (D_SUMMARY) {
	    fprintf(stderr,
	      "%s: new: %s dir not found or is empty\n",
	      program, grp->name);
	}
	return NEWGRP_EMPTY;
    }


    if (newhi == oldhi && newlow == oldlow) {


	if (D_SUMMARY) {
	    fprintf(stderr,
	      "%s: new: %s, non-empty dir, no hi/low water change\n",
	      program, grp->name);
	}
	return NEWGRP_NOCHG;
    }


    if (newhi != oldhi) {
	hi = malloc(WATER_LEN+1);
	if (hi == NULL) {
	    fprintf(stderr,
		"%s: unable to malloc %d octet hi water string\n",
		program, WATER_LEN+1);
	    exit(54);
	}
	sprintf(hi, "%010ld", newhi);
	if (D_BUG) {
	    fprintf(stderr,
	      "%s: new: %s, dir found, oldhi:<%s> != newhi:<%s>\n",
	      program, grp->name, grp->outhi, hi);
	}
	grp->outhi = hi;
    }
    if (newlow != oldlow) {
	low = malloc(WATER_LEN+1);
	if (low == NULL) {
	    fprintf(stderr,
		"%s: unable to malloc %d octet low water string\n",
		program, WATER_LEN+1);
	    exit(55);
	}
	sprintf(low, "%010ld", newlow);
	if (D_BUG) {
	    fprintf(stderr,
	      "%s: new: %s, dir found, oldlow:<%s> != newlow:<%s>\n",
	      program, grp->name, grp->outlow, low);
	}
	grp->outlow = low;
    }


    return NEWGRP_CHG;
}
