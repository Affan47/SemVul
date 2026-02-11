load_file(const GURL &url)
{
  DEBUG_MSG("FCPools::load_file: url='" << url << "'\n");
  DEBUG_MAKE_INDENT(3);
  GCriticalSectionLock lock(&map_lock);

  clean();
   if (url.is_local_file_url())
   {
      GPosition pos;
      if (map.contains(url, pos))
      {


	 GPList<DataPool> list=map[pos];
	 for(GPosition list_pos=list;list_pos;++list_pos)
	    list[list_pos]->load_file();
      }
   }
}
