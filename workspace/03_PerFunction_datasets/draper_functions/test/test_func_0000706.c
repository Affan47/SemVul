_browse(Evry_Plugin *plugin, const Evry_Item *it)
{
   Plugin *p = NULL;

   if (!it || !(CHECK_TYPE(it, EVRY_TYPE_FILE)))
     return NULL;

   GET_FILE(file, it);

   if (!evry->file_path_get(file) ||
       !ecore_file_is_dir(file->path))
     return NULL;

   EVRY_PLUGIN_INSTANCE(p, plugin);

   p->directory = eina_stringshare_add(file->path);
   p->parent = EINA_TRUE;

   _read_directory(p);

   return EVRY_PLUGIN(p);
}
