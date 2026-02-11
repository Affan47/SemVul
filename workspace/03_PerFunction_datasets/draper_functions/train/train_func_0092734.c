ncattrename(cdfid, varid, name, newname)
int cdfid ;
int varid ;
const char *name ;
const char *newname ;
{

	NC *handle ;
	NC_attr **attr ;
	NC_string *new, *old ;

	cdf_routine_name = "cdfattrrename" ;

	handle = NC_check_id(cdfid) ;
	if(handle == NULL)
		return(-1) ;
	if(!(handle->flags & NC_RDWR))
		return(-1) ;

	attr = NC_lookupattr(cdfid,varid,name,TRUE) ;
	if(attr == NULL)
		return(-1) ;

	if( NC_lookupattr(cdfid,varid,newname,FALSE) != NULL)
		return(-1) ;

	old = (*attr)->name ;
	if( NC_indefine(cdfid,FALSE) )
	{
		new = NC_new_string((unsigned)strlen(newname),newname) ;
		if( new == NULL)
			return(-1) ;
		(*attr)->name = new ;
		NC_free_string(old) ;
		return(1) ;
	}
	new = NC_re_string(old, (unsigned)strlen(newname),newname) ;
	if( new == NULL)
		return(-1) ;
	(*attr)->name = new ;
	if(handle->flags & NC_HSYNC)
	{
		handle->xdrs->x_op = XDR_ENCODE ;
		if(!xdr_cdf(handle->xdrs, &handle) )
			return(-1) ;
		handle->flags &= ~(NC_NDIRTY | NC_HDIRTY) ;
	} else
		handle->flags |= NC_HDIRTY ;
	return(1) ;
}
