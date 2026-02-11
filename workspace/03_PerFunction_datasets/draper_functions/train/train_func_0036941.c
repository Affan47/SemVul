gftp_gtk_save_bookmark_options ()
{
  gftp_config_vars * cv;
  GList * templist;
  int i;

  for (templist = gftp_options_list;
       templist != NULL;
       templist = templist->next)
    {
      cv = templist->data;

      for (i=0; cv[i].key != NULL; i++)
        {
          if (!(cv[i].flags & GFTP_CVARS_FLAGS_SHOW_BOOKMARK))
            continue;

          if (gftp_option_types[cv[i].otype].ui_save_function == NULL)
            continue;

          gftp_option_types[cv[i].otype].ui_save_function (&cv[i],
                                                           gftp_option_data);
        }
    }
}
