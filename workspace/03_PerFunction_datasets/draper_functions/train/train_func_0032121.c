c_ncvptg (
    int			ncid,
    int			varid,
    const size_t*	start,
    const size_t*	count,
    const ptrdiff_t*	strides,
    const ptrdiff_t*	imap,
    const void*		value,
    int*		rcode
)
{
    int		status;
    int		rank;
    nc_type	datatype;

    if ((status = nc_inq_vartype(ncid, varid, &datatype)) == 0 &&
	(status = nc_inq_varndims(ncid, varid, &rank)) == 0)
    {
	switch (datatype)
	{
	case NC_CHAR:
	    status = NC_ECHAR;
	    break;
	case NC_BYTE:
#	    if NF_INT1_IS_C_SIGNED_CHAR
		status = nc_put_varm_schar(ncid, varid, start, count,
					   strides, imap,
					   (const signed char*)value);
#	    elif NF_INT1_IS_C_SHORT
		status = nc_put_varm_short(ncid, varid, start, count,
					   strides, imap,
					   (const short*)value);
#	    elif NF_INT1_IS_C_INT
		status = nc_put_varm_int(ncid, varid, start, count,
					   strides, imap,
					   (const int*)value);
#	    elif NF_INT1_IS_C_LONG
		status = nc_put_varm_long(ncid, varid, start, count,
					   strides, imap,
					   (const long*)value);
#	    endif
	    break;
	case NC_SHORT:
#	    if NF_INT2_IS_C_SHORT
		status = nc_put_varm_short(ncid, varid, start, count,
					   strides, imap,
					   (const short*)value);
#	    elif NF_INT2_IS_C_INT
		status = nc_put_varm_int(ncid, varid, start, count,
					   strides, imap,
					   (const int*)value);
#	    elif NF_INT2_IS_C_LONG
		status = nc_put_varm_long(ncid, varid, start, count,
					   strides, imap,
					   (const long*)value);
#	    endif
	    break;
	case NC_INT:
#	    if NF_INT_IS_C_INT
		status = nc_put_varm_int(ncid, varid, start, count,
					   strides, imap,
					   (const int*)value);
#	    elif NF_INT_IS_C_LONG
		status = nc_put_varm_long(ncid, varid, start, count,
					   strides, imap,
					   (const long*)value);
#	    endif
	    break;
	case NC_FLOAT:
#	    if NF_REAL_IS_C_FLOAT
		status = nc_put_varm_float(ncid, varid, start, count,
					   strides, imap,
					   (const float*)value);
#	    elif NF_REAL_IS_C_DOUBLE
		status = nc_put_varm_double(ncid, varid, start, count,
					   strides, imap,
					   (const double*)value);
#	    endif
	    break;
	case NC_DOUBLE:
#	    if NF_DOUBLEPRECISION_IS_C_FLOAT
		status = nc_put_varm_float(ncid, varid, start, count,
					   strides, imap,
					   (const float*)value);
#	    elif NF_DOUBLEPRECISION_IS_C_DOUBLE
		status = nc_put_varm_double(ncid, varid, start, count,
					   strides, imap,
					   (const double*)value);
#	    endif
	    break;
	}
    }

    if (status == 0)
	*rcode = 0;
    else
    {
	nc_advise("NCVPTG", status, "");
	*rcode = ncerr;
    }
}
