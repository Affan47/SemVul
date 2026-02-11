add_att(NcToken aname, int len, const ncbyte* vals)
{
    if (! the_file->define_mode())
      return FALSE;
    if (NcError::set_err(
			 nc_put_att_schar (the_file->id(), the_id, aname, (nc_type) NcTypeEnum(ncbyte),
		 len, vals)
			 ) != NC_NOERR)
      return FALSE;
    return TRUE;
}
