stpui_get_system_printers(void)
{
  FILE *pfile;
  char  line[1025];

  stpui_system_print_queues = stp_string_list_create();
  stp_string_list_add_string_unsafe(stpui_system_print_queues, "",
				    _("(Default Printer)"));


  identify_print_system();
  if (global_printing_system)
  {
    const char *old_locale = getenv("LC_ALL");
    const char *old_lc_messages = getenv("LC_MESSAGES");
    const char *old_lang = getenv("LANG");
    (void) setenv("LC_ALL", "C", 1);
    (void) setenv("LC_MESSAGES", "C", 1);
    (void) setenv("LANG", "C", 1);
    if ((pfile = popen(global_printing_system->scan_command, "r")) != NULL)
    {


      while (fgets(line, sizeof(line), pfile) != NULL)
	{
	  char *tmp_ptr;
	  if ((tmp_ptr = strchr(line, '\n')))
	    tmp_ptr[0] = '\0';
	  if ((tmp_ptr = strchr(line, '\r')))
	    tmp_ptr[0] = '\0';
	  if (strlen(line) > 0)
	    {
	      if (!stp_string_list_is_present(stpui_system_print_queues, line))
		stp_string_list_add_string_unsafe(stpui_system_print_queues,
						  line, line);
	    }
	}
      pclose(pfile);
      if (old_locale)
	setenv("LC_ALL", old_locale, 1);
      else
	unsetenv("LC_ALL");
      if (old_lc_messages)
	setenv("LC_MESSAGES", old_lc_messages, 1);
      else
	unsetenv("LC_MESSAGES");
      if (old_lang)
	setenv("LANG", old_lang, 1);
      else
	unsetenv("LANG");
    }
  }
}
