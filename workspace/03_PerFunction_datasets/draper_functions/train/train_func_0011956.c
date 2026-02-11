gd_tagged_entry_tag_get_size (GdTaggedEntryTag *tag,
                              GdTaggedEntry *entry,
                              gint *width_out,
                              gint *height_out)
{
  gint width, panel_height;

  width = gd_tagged_entry_tag_get_width (tag, entry);
  panel_height = gd_tagged_entry_tag_panel_get_height (entry);

  if (width_out)
    *width_out = width;
  if (height_out)
    *height_out = panel_height;
}
