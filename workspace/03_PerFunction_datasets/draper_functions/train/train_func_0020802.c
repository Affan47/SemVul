gd_tagged_entry_tag_event_is_button (GdTaggedEntryTag *tag,
                                     GdTaggedEntry *entry,
                                     gdouble event_x,
                                     gdouble event_y)
{
  GtkAllocation button_allocation;
  GtkStyleContext *context;

  if (!entry->priv->button_visible)
    return FALSE;

  context = gd_tagged_entry_tag_get_context (entry);
  gd_tagged_entry_tag_get_relative_allocations (tag, entry, context, NULL, NULL, &button_allocation);

  g_object_unref (context);


  if ((event_x >= button_allocation.x &&
       event_x <= button_allocation.x + button_allocation.width) &&
      (event_y >= button_allocation.y &&
       event_y <= button_allocation.y + button_allocation.height))
    return TRUE;

  return FALSE;
}
