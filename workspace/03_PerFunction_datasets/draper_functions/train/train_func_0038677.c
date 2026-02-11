stp_escp2_load_input_slots(const stp_vars_t *v, const char *name)
{
  stpi_escp2_printer_t *printdef = stp_escp2_get_printer(v);
  stp_list_t *dirlist = stpi_data_path();
  stp_list_item_t *item;
  int found = 0;
  item = stp_list_get_start(dirlist);
  while (item)
    {
      const char *dn = (const char *) stp_list_item_get_data(item);
      char *ffn = stpi_path_merge(dn, name);
      stp_mxml_node_t *slots =
	stp_mxmlLoadFromFile(NULL, ffn, STP_MXML_NO_CALLBACK);
      stp_free(ffn);
      if (slots)
	{
	  stp_mxml_node_t **xnode =
	    (stp_mxml_node_t **) &(printdef->slots);
	  stp_list_t **xlist =
	    (stp_list_t **) &(printdef->slots_cache);
	  stp_string_list_t **xslots =
	    (stp_string_list_t **) &(printdef->input_slots);
	  stp_mxml_node_t *node = stp_mxmlFindElement(slots, slots,
						      "escp2InputSlots", NULL,
						      NULL, STP_MXML_DESCEND);
	  *xnode = slots;
	  *xlist = stp_list_create();
	  stp_list_set_namefunc(*xlist, slots_namefunc);
	  *xslots = stp_string_list_create();
	  if (node)
	    {
	      node = node->child;
	      while (node)
		{
		  if (node->type == STP_MXML_ELEMENT &&
		      strcmp(node->value.element.name, "slot") == 0)
		    stp_string_list_add_string(*xslots,
					       stp_mxmlElementGetAttr(node, "name"),
					       stp_mxmlElementGetAttr(node, "text"));
		  node = node->next;
		}
	    }
	  found = 1;
	  break;
	}
      item = stp_list_item_next(item);
    }
  stp_list_destroy(dirlist);
  STPI_ASSERT(found, v);
  return found;
}
