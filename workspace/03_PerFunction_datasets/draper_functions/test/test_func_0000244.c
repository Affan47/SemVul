fill_helper_lists(const StringList & def_dirs)
  {
    dict_dirs = def_dirs;
    dict_exts.append(DictExt(0, ".awli"));

    for (ModuleInfoNode * n = module_info_list.head_; n != 0; n = n->next)
    {
      {
	StringListEnumeration e = n->dict_dirs.elements_obj();
	const char * item;
	while ( (item = e.next()) != 0 )
	  dict_dirs.add(item);
      }{
	StringListEnumeration e = n->dict_exts.elements_obj();
	const char * item;
	while ( (item = e.next()) != 0 )
	  dict_exts.append(DictExt(&n->c_struct, item));
      }
    }
  }
