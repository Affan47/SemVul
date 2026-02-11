stp_get_printer_by_foomatic_id(const char *foomatic_id)
{
  stp_list_item_t *printer_item;
  if (printer_list == NULL)
    {
      stp_erprintf("No printer drivers found: "
		   "are STP_DATA_PATH and STP_MODULE_PATH correct?\n");
      stpi_init_printer_list();
    }
  if (! foomatic_id || strcmp(foomatic_id, "") == 0)
    return NULL;

  printer_item = stp_list_get_start(printer_list);
  while (printer_item)
    {
      if (strcmp(((const stp_printer_t *) stp_list_item_get_data(printer_item))->foomatic_id,
		 foomatic_id) == 0)
	return ((const stp_printer_t *) stp_list_item_get_data(printer_item));
      printer_item = stp_list_item_next(printer_item);
    }
  return NULL;
}
