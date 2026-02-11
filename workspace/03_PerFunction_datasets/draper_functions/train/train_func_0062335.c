gd_tagged_entry_tag_get_relative_allocations (GdTaggedEntryTag *tag,
                                              GdTaggedEntry *entry,
                                              GtkStyleContext *context,
                                              GtkAllocation *background_allocation_out,
                                              GtkAllocation *layout_allocation_out,
                                              GtkAllocation *button_allocation_out)
{
  GtkAllocation background_allocation, layout_allocation, button_allocation;
  gint width, height, x, y, pix_width, pix_height;
  gint layout_width, layout_height;
  GtkBorder padding, border;
  GtkStateFlags state;

  width = gdk_window_get_width (tag->priv->window);
  height = gdk_window_get_height (tag->priv->window);

  state = gd_tagged_entry_tag_get_state (tag, entry);
  gtk_style_context_get_margin (context, state, &padding);

  width -= padding.left + padding.right;
  height -= padding.top + padding.bottom;
  x = padding.left;
  y = padding.top;

  background_allocation.x = x;
  background_allocation.y = y;
  background_allocation.width = width;
  background_allocation.height = height;

  layout_allocation = button_allocation = background_allocation;

  gtk_style_context_get_padding (context, state, &padding);
  gtk_style_context_get_border (context, state, &border);

  gd_tagged_entry_tag_ensure_layout (tag, entry);
  pango_layout_get_pixel_size (tag->priv->layout, &layout_width, &layout_height);

  layout_allocation.x += border.left + padding.left;
  layout_allocation.y += (layout_allocation.height - layout_height) / 2;

  if (entry->priv->button_visible && tag->priv->has_close_button)
    {
      pix_width = gdk_pixbuf_get_width (tag->priv->close_pixbuf);
      pix_height = gdk_pixbuf_get_height (tag->priv->close_pixbuf);
    }
  else
    {
      pix_width = 0;
      pix_height = 0;
    }

  button_allocation.x += width - pix_width - border.right - padding.right;
  button_allocation.y += (height - pix_height) / 2;
  button_allocation.width = pix_width;
  button_allocation.height = pix_height;

  if (background_allocation_out)
    *background_allocation_out = background_allocation;
  if (layout_allocation_out)
    *layout_allocation_out = layout_allocation;
  if (button_allocation_out)
    *button_allocation_out = button_allocation;
}
