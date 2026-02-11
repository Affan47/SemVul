_check_range(struct tree *tp, long ltmp, int *resptr,
	                const char *errmsg)
{
    char *cp   = NULL;
    char *temp = NULL;
    int   temp_len = 0;
    int check = !netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
	                                NETSNMP_DS_LIB_DONT_CHECK_RANGE);

    if (check && tp && tp->ranges) {
	struct range_list *rp = tp->ranges;
	while (rp) {
	    if (rp->low <= ltmp && ltmp <= rp->high) break;

            temp_len += ((rp->low != rp->high) ? 14 : 8 );
	    rp = rp->next;
	}
	if (!rp) {
	    *resptr = SNMPERR_RANGE;
            temp = (char *)malloc( temp_len+strlen(errmsg)+7);
            if ( temp ) {

                sprintf( temp, "%s :: {", errmsg );
                cp = temp+(strlen(temp));
                for ( rp = tp->ranges; rp; rp=rp->next ) {
                    if ( rp->low != rp->high )
                        sprintf( cp, "(%d..%d), ", rp->low, rp->high );
                    else
                        sprintf( cp, "(%d), ", rp->low );
                    cp += strlen(cp);
                }
                *(cp-2) = '}';
                *(cp-1) = 0;
	        snmp_set_detail(temp);
	        free(temp);
            }
	    return 0;
	}
    }
    free(temp);
    return 1;
}
