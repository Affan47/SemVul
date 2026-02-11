_gdbm_end_update (dbf)
     gdbm_file_info *dbf;
{
  int  num_bytes;
  off_t file_pos;


  if (dbf->bucket_changed && (dbf->cache_entry != NULL))
    {
      _gdbm_write_bucket (dbf, dbf->cache_entry);
      dbf->bucket_changed = FALSE;
    }


  if (dbf->second_changed)
    {
      if(dbf->bucket_cache != NULL)
        {
          register int index;

          for (index = 0; index < dbf->cache_size; index++)
	    {
	      if (dbf->bucket_cache[index].ca_changed)
	        _gdbm_write_bucket (dbf, &dbf->bucket_cache[index]);
            }
        }
      dbf->second_changed = FALSE;
    }


  if (dbf->directory_changed)
    {
      file_pos = lseek (dbf->desc, dbf->header->dir, L_SET);
      if (file_pos != dbf->header->dir) _gdbm_fatal (dbf, "lseek error");
      num_bytes = write (dbf->desc, dbf->dir, dbf->header->dir_size);
      if (num_bytes != dbf->header->dir_size)
	_gdbm_fatal (dbf, "write error");
      dbf->directory_changed = FALSE;
      if (!dbf->header_changed && !dbf->fast_write)
	fsync (dbf->desc);
    }


  if (dbf->header_changed)
    {
      write_header (dbf);
      dbf->header_changed = FALSE;
    }
}
