NC_reccpy( target, old, varid, recnum)
XDR *target ;
NC *old ;
int varid ;
int recnum ;
{
	NC_var **vpp ;
	vpp = (NC_var **)old->vars->values ;
	vpp += varid ;

	if( !xdr_setpos(old->xdrs,
                    (*vpp)->begin + old->recsize*recnum )){
		NCadvise(NC_EXDR, "NC_reccpy: xdr_setpos") ;
		return(FALSE) ;
	}

	return(NC_dcpy(target, old->xdrs, (*vpp)->len)) ;
}
