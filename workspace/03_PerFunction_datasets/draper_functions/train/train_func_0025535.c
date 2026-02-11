xsh_print_cpl_propertylist (const cpl_propertylist * pl, long low, long high)
{
  cpl_property *prop;
  long i = 0;

  assure (0 <= low && high <= cpl_propertylist_get_size (pl) && low <= high,
	  CPL_ERROR_ILLEGAL_INPUT, "Illegal range");


  if (pl == NULL) {
    xsh_msg ("NULL");
  }
  else if (cpl_propertylist_is_empty (pl)) {
    xsh_msg ("[Empty property list]");
  }
  else
    for (i = low; i < high; i++) {


      prop = cpl_propertylist_get ((cpl_propertylist *) pl, i);
      check (xsh_print_cpl_property (prop));
    }

cleanup:
  return cpl_error_get_code ();
}
