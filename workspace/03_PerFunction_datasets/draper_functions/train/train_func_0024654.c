ncsync(id)
int id ;
{
	NC *handle ;

	cdf_routine_name = "ncsync" ;

	handle = NC_check_id(id) ;
	if(handle == NULL)
		return(-1) ;

	if( handle->flags & NC_INDEF )
      {
          NCadvise(NC_EINDEFINE, "Unfinished definition") ;
          return(-1) ;
      }

	if(handle->flags & NC_RDWR)
      {
          handle->xdrs->x_op = XDR_ENCODE ;
          if(handle->flags & NC_HDIRTY)
            {
                if(!xdr_cdf(handle->xdrs, &handle) )
                    return(-1) ;
                handle->flags &= ~(NC_NDIRTY | NC_HDIRTY) ;
            }
          else if(handle->flags & NC_NDIRTY)
            {
                if(!xdr_numrecs(handle->xdrs, handle) )
                    return(-1) ;
#ifdef HDF
                if (handle->file_type != HDF_FILE)
#endif
                    handle->flags &= ~(NC_NDIRTY) ;
            }
      }
    else
      {


          handle->xdrs->x_op = XDR_FREE ;
          (void) xdr_cdf(handle->xdrs, &handle) ;
          handle->xdrs->x_op = XDR_DECODE ;

          if(!xdr_cdf(handle->xdrs, &handle) )
            {
                nc_serror("xdr_cdf") ;
                NC_free_cdf(handle) ;

#if 0

		if (_ncdf == 0)
		    ncreset_cdflist();
#endif
                return(-1) ;
            }
          if( NC_computeshapes(handle) == -1)
              return(-1) ;
      }

	(void) NCxdrfile_sync(handle->xdrs) ;

	return(0) ;
}
