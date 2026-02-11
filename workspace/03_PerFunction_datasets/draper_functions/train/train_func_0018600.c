add_file_to_djvm(const GP<DjVuFile> & file, bool page,
		 DjVmDoc & doc, GMap<GURL, void *> & map,
                 bool &needs_compression_flag, bool &can_compress_flag )
{
  if(!needs_compression_flag)
  {
    if(file->needs_compression())
    {
      can_compress_flag=true;
      needs_compression_flag=true;
    }else if(file->can_compress())
    {
      can_compress_flag=true;
    }
  }
  add_file_to_djvm(file,page,doc,map);
}
