get( char* vals,
		     long edge0,
		     long edge1,
		     long edge2,
		     long edge3,
		     long edge4) const
{
    if (! the_file->data_mode())
      return FALSE;
    size_t count[5];
    count[0] = edge0;
    count[1] = edge1;
    count[2] = edge2;
    count[3] = edge3;
    count[4] = edge4;
    for (int i = 0; i < 5; i++) {
	if (count[i]) {
	    if (num_dims() < i)
	      return FALSE;
	} else
	  break;
    }
    size_t start[5];
    for (int j = 0; j < 5; j++) {
     start[j] = the_cur[j];
    }
    return NcError::set_err(
			    nc_get_vara_text (the_file->id(), the_id, start, count, vals)
			    ) == NC_NOERR;
}
