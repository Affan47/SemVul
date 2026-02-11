add_usbid (usbid_type *first_usbid, char *manufacturer, char *model,
	   char *usb_vendor_id, char *usb_product_id)
{
  usbid_type *usbid = first_usbid;
  usbid_type *prev_usbid = 0, *tmp_usbid = 0;

  if (!first_usbid)
    first_usbid = create_usbid (manufacturer, model, usb_vendor_id, usb_product_id);
  else
    {
      while (usbid)
	{
	  if (strcmp (usb_vendor_id, usbid->usb_vendor_id) == 0 &&
	      strcmp (usb_product_id, usbid->usb_product_id) == 0)
	    {
	      manufacturer_model_type *man_mod = usbid->name;

	      while (man_mod->next)
		man_mod = man_mod->next;
	      man_mod->next = malloc (sizeof (manufacturer_model_type));
	      man_mod->next->name = malloc (strlen (manufacturer) + strlen (model) + 3);
	      sprintf (man_mod->next->name, "%s %s", manufacturer, model);
	      man_mod->next->next = 0;
	      DBG_DBG ("Added manufacturer/model %s %s to USB ids %s/%s\n", manufacturer, model,
			usb_vendor_id, usb_product_id);
	      break;
	    }
	  if (strcmp (usb_vendor_id, usbid->usb_vendor_id) < 0 ||
	      (strcmp (usb_vendor_id, usbid->usb_vendor_id) == 0 &&
	       strcmp (usb_product_id, usbid->usb_product_id) < 0))
	    {

	      tmp_usbid = create_usbid (manufacturer, model, usb_vendor_id, usb_product_id);
	      tmp_usbid->next = usbid;
	      if (prev_usbid)
		prev_usbid->next = tmp_usbid;
	      else
		first_usbid = tmp_usbid;
	      break;
	    }
	  prev_usbid = usbid;
	  usbid = usbid->next;
	}
      if (!usbid)
	{
	  prev_usbid->next = create_usbid (manufacturer, model, usb_vendor_id, usb_product_id);
	  usbid = prev_usbid->next;
	}
    }
  return first_usbid;
}
