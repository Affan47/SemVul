get_info(const GP<DjVuFile> & file) const
{
   if (file->info)
   {
     if(rotate_count<0)
     {
       const_cast<DjVuImage *>(this)->init_rotate(*(file->info));
     }
     return file->info;
   }
   GPList<DjVuFile> list=file->get_included_files();
   for(GPosition pos=list;pos;++pos)
   {
      GP<DjVuInfo> info=get_info(list[pos]);
      if (info)
      {
        if(rotate_count<0)
        {
          const_cast<DjVuImage *>(this)->init_rotate(*(file->info));
        }
        return info;
      }
   }
   return 0;
}
