_deregister_keygrab (SpiDEController      *controller,
		     DEControllerGrabMask *grab_mask)
{
  GList *l;

  l = g_list_find_custom (controller->keygrabs_list, grab_mask,
			  spi_grab_mask_compare_values);

  if (l)
    {
      DEControllerGrabMask *cur_mask = l->data;

      cur_mask->ref_count--;
      if (cur_mask->ref_count <= 0)
        {
          cur_mask->pending_remove = TRUE;
	}
    }
}
