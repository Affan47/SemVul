update_scenario_page(void)
{
  struct fileinfo_list *files;

  gtk_list_store_clear(scenario_store);


  files = fileinfolist_infix(get_scenario_dirs(), ".sav", TRUE);
  fileinfo_list_iterate(files, pfile) {
    GtkTreeIter it;
    struct section_file *sf;

    gtk_list_store_append(scenario_store, &it);

    if ((sf = secfile_load_section(pfile->fullname, "scenario", TRUE))) {
      const char *sname, *sdescription;

      sname = secfile_lookup_str_default(sf, NULL, "scenario.name");
      sdescription = secfile_lookup_str_default(sf, NULL,
                                                "scenario.description");
      gtk_list_store_set(scenario_store, &it,
                         0, sname && strlen(sname) ? Q_(sname) : pfile->name,
                         1, pfile->fullname,
                         2, (NULL != sdescription && '\0' != sdescription[0]
                             ? Q_(sdescription) : ""),
                         -1);
      secfile_destroy(sf);
    } else {
      log_error("Error loading '%s':\n%s", pfile->fullname, secfile_error());
      gtk_list_store_set(scenario_store, &it,
			 0, pfile->name,
			 1, pfile->fullname,
			 2, "",
			-1);
    }
  } fileinfo_list_iterate_end;

  fileinfo_list_destroy(files);
}
