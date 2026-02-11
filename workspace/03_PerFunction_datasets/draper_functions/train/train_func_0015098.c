xdr_numrecs(xdrs, handle)
	XDR *xdrs;
	NC *handle;
{

#ifdef HDF
    if(handle->file_type == HDF_FILE)
        return TRUE;
#endif

	if( (handle->flags & NC_NOFILL)
		&& xdrs->x_op == XDR_ENCODE
		&& handle->begin_rec > 0)
      {


          if( !xdr_setpos(xdrs, handle->begin_rec
                          +  handle->numrecs * handle->recsize) )
            {
                nc_serror("Can't set position to EOF") ;
                return(FALSE) ;
            }
#ifdef RDEBUG
          fprintf(stderr,"\txdr_numrecs %ld = %d + %ld * %d\n",
                  xdr_getpos(xdrs),
                  handle->begin_rec, handle->numrecs, handle->recsize) ;
#endif
          if( !xdr_u_long(xdrs, &(handle->numrecs)) )
              return(FALSE) ;
      }

	if( !xdr_setpos(xdrs, RECPOS) )
      {
          nc_serror("Can't set position to RECPOS") ;
          return(FALSE) ;
      }
	return( xdr_u_long(xdrs, &(handle->numrecs)) ) ;
}
