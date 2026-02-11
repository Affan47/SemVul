insert_poly(Tcl_Interp * interp, vgpane_t * vgp, int polyid, char *vargv[],
	    int vargc)
{
    poly *np;
    int i, result;

    np = allocpoly(vgp, polyid, vargc);
    for (i = 0; i < vargc; i += 2) {
	result =
	    scanpoint(interp, &vargv[i],
		      &(np->boundary.ps[np->boundary.pn]));
	if (result != TCL_OK)
	    return result;
	np->boundary.pn++;
    }
    make_CW(&(np->boundary));
    vc_stale(vgp);
    return TCL_OK;
}
