rec_dim( ) const
{
    if (! is_valid())
      return 0;
    int recdim;
    if(NcError::set_err(
                        nc_inq_unlimdim(the_id, &recdim)
                        ) != NC_NOERR)
        return 0;
    return get_dim(recdim);
}
