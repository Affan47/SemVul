u_left_shop(leavestring, newlev)
char *leavestring;
boolean newlev;
{
	struct monst *shkp;
	struct eshk *eshkp;


	if(!*leavestring &&
	   (!levl[u.ux][u.uy].edge || levl[u.ux0][u.uy0].edge))
	    return;

	shkp = shop_keeper(*u.ushops0);
	if (!shkp || !inhishop(shkp))
	    return;

	eshkp = ESHK(shkp);
	if (!eshkp->billct && !eshkp->debit)
	    return;

	if (!*leavestring && shkp->mcanmove && !shkp->msleeping) {


	    verbalize(NOTANGRY(shkp) ?
		      "%s!  Please pay before leaving." :
		      "%s!  Don't you leave without paying!",
		      plname);
	    return;
	}

	if (rob_shop(shkp)) {
#ifdef KOPS
	    call_kops(shkp, (!newlev && levl[u.ux0][u.uy0].edge));
#else
	    (void) angry_guards(FALSE);
#endif
	}
}
