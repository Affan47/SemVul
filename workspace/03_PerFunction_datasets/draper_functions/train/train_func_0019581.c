find_files_handlerton(THD *thd, plugin_ref plugin,
                                   void *arg)
{
  st_find_files_args *vargs= (st_find_files_args *)arg;
  handlerton *hton= plugin_data(plugin, handlerton *);


  if (hton->state == SHOW_OPTION_YES && hton->find_files)
      if (hton->find_files(hton, thd, vargs->db, vargs->path, vargs->wild,
                          vargs->dir, vargs->files))
        return TRUE;

  return FALSE;
}
