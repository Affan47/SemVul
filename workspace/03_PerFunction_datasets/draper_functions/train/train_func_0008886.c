get_format( void ) const
{
    int the_format;
    NcError::set_err(
		     nc_inq_format(the_id, &the_format)
		     );
    switch (the_format) {
    case NC_FORMAT_CLASSIC:
	return Classic;
    case NC_FORMAT_64BIT:
	return Offset64Bits;
    case NC_FORMAT_NETCDF4:
	return Netcdf4;
    case NC_FORMAT_NETCDF4_CLASSIC:
	return Netcdf4Classic;
    default:
	return BadFormat;
    }
}
