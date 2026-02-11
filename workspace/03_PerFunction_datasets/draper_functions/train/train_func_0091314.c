add_file(const GP<DjVuFile> & file)
{
   DEBUG_MSG("DjVuFileCache::add_file(): trying to add a new item\n");
   DEBUG_MAKE_INDENT(3);

   GCriticalSectionLock lock(&class_lock);


   GPosition pos;
   for(pos=list;pos;++pos)
      if (list[pos]->get_file()==file) break;

   if (pos) list[pos]->refresh();
   else
   {

      int _max_size=enabled ? max_size : 0;
      if (max_size<0) _max_size=max_size;

      int add_size=file->get_memory_usage();

      if (_max_size>=0 && add_size>_max_size)
      {
	 DEBUG_MSG("but this item is way too large => doing nothing\n");
	 return;
      }

      if (_max_size>=0) clear_to_size(_max_size-add_size);

      list.append(new Item(file));
      cur_size+=add_size;
      file_added(file);
   }
}
