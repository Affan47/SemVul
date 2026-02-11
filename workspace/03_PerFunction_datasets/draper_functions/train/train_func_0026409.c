stpui_plist_add(const stpui_plist_t *key, int add_only)
{


  stpui_plist_t *p;
  if (!stp_get_printer(key->v))
    stp_set_driver(key->v, "ps2");
  if (stp_get_printer(key->v))
    {
      p = psearch(key, stpui_plist, stpui_plist_count,
		  sizeof(stpui_plist_t),
		  (int (*)(const void *, const void *)) compare_printers);
      if (p == NULL)
	{
#ifdef DEBUG
	  fprintf(stderr, "Adding new printer from printrc file: %s\n",
		  key->name);
#endif
	  check_plist(stpui_plist_count + 1);
	  p = stpui_plist + stpui_plist_count;
	  stpui_plist_count++;
	  stpui_plist_copy(p, key);
	  if (strlen(stpui_plist_get_queue_name(p)) == 0 &&
	      stp_string_list_is_present(stpui_system_print_queues,
					 stpui_plist_get_name(p)))
	    stpui_plist_set_queue_name(p, stpui_plist_get_name(p));
	}
      else
	{
	  if (add_only)
	    return 0;
#ifdef DEBUG
	  fprintf(stderr, "Updating printer %s.\n", key->name);
#endif
	  stpui_plist_copy(p, key);
	}
      return 1;
    }
  else
    {
      fprintf(stderr, "No printer found!\n");
      return 0;
    }
}
