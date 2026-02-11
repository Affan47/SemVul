display_th44(ByteStream & out_str, IFFByteStream & iff,
	     GUTF8String, size_t, DjVmInfo & djvminfo, int counter)
{
   int start_page=-1;
   if (djvminfo.dir)
   {
      GPList<DjVmDir::File> files_list=djvminfo.dir->get_files_list();
      for(GPosition pos=files_list;pos;++pos)
      {
	 GP<DjVmDir::File> frec=files_list[pos];
	 if (iff.tell()>=frec->offset &&
	     iff.tell()<frec->offset+frec->size)
	 {
	    while(pos && !files_list[pos]->is_page())
	       ++pos;
	    if (pos)
	       start_page=files_list[pos]->get_page_num();
	    break;
	 }
      }
   }
   if (start_page>=0)
      out_str.format( "Thumbnail icon for page %d", start_page+counter+1);
   else
      out_str.format( "Thumbnail icon");
}
