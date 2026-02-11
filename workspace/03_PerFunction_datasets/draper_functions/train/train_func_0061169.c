notify_file_flags_changed(const DjVuFile * source,
					long set_mask, long clr_mask)
{


   if (set_mask & DjVuFile::DECODE_OK)
   {
      set_file_aliases(source);
      if (cache) add_to_cache((DjVuFile *) source);
      if(!needs_compression_flag)
      {
        if(source->needs_compression())
        {
          can_compress_flag=true;
          needs_compression_flag=true;
        }else if(source->can_compress())
        {
          can_compress_flag=true;
        }
      }
   }
   process_threqs();
}
