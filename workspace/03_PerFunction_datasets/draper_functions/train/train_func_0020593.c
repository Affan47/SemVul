c_ncagt(
    int		ncid,
    int		varid,
    const char*	attname,
    void*	value,
    int*	rcode
)
{
    int		status;
    nc_type	datatype;

    if ((status = nc_inq_atttype(ncid, varid, attname, &datatype)) == 0)
    {
	switch (datatype)
	{
	case NC_CHAR:
	    status = NC_ECHAR;
	    break;
	case NC_BYTE:
#    	if NF_INT1_IS_C_SIGNED_CHAR
		status = nc_get_att_schar(ncid, varid, attname,
					   (signed char*)value);
#    	elif NF_INT1_IS_C_SHORT
		status = nc_get_att_short(ncid, varid, attname,
					   (short*)value);
#    	elif NF_INT1_IS_C_INT
		status = nc_get_att_int(ncid, varid, attname,
					   (int*)value);
#    	elif NF_INT1_IS_C_LONG
		status = nc_get_att_long(ncid, varid, attname,
					   (long*)value);
#    	endif
	    break;
	case NC_SHORT:
#    	if NF_INT2_IS_C_SHORT
		status = nc_get_att_short(ncid, varid, attname,
					   (short*)value);
#    	elif NF_INT2_IS_C_INT
		status = nc_get_att_int(ncid, varid, attname,
					   (int*)value);
#    	elif NF_INT2_IS_C_LONG
		status = nc_get_att_long(ncid, varid, attname,
					   (long*)value);
#    	endif
	    break;
	case NC_INT:
#	    if NF_INT_IS_C_INT
		status = nc_get_att_int(ncid, varid, attname,
					   (int*)value);
#	    elif NF_INT_IS_C_LONG
		status = nc_get_att_long(ncid, varid, attname,
					   (long*)value);
#	    endif
	    break;
	case NC_FLOAT:
#    	if NF_REAL_IS_C_FLOAT
		status = nc_get_att_float(ncid, varid, attname,
					   (float*)value);
#    	elif NF_REAL_IS_C_DOUBLE
		status = nc_get_att_double(ncid, varid, attname,
					   (double*)value);
#    	endif
	    break;
	case NC_DOUBLE:
#    	if NF_DOUBLEPRECISION_IS_C_FLOAT
		status = nc_get_att_float(ncid, varid, attname,
					   (float*)value);
#    	elif NF_DOUBLEPRECISION_IS_C_DOUBLE
		status = nc_get_att_double(ncid, varid, attname,
					   (double*)value);
#    	endif
	    break;
	}
    }

    if (status == 0)
	*rcode = 0;
    else
    {
	nc_advise("NCAGT", status, "");
	*rcode = ncerr;
    }
}
