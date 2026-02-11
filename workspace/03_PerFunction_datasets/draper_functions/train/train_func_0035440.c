render_slice (GduVolumeGrid *grid,
              cairo_t       *cr,
              GList         *elements)
{
  GList *l;
  gboolean animate_spinner;

  animate_spinner = FALSE;
  for (l = elements; l != NULL; l = l->next)
    {
      GridElement *element = l->data;
      gboolean is_selected;
      gboolean is_focused;
      gboolean is_grid_focused;

      is_selected = FALSE;
      is_focused = FALSE;
      is_grid_focused = gtk_widget_has_focus (GTK_WIDGET (grid));

      if (element == grid->selected)
        is_selected = TRUE;

      if (element == grid->focused)
        {
          if (is_grid_focused)
            is_focused = TRUE;
        }

      animate_spinner |= render_element (grid,
                                         cr,
                                         element,
                                         is_selected,
                                         is_focused,
                                         is_grid_focused);

      animate_spinner |= render_slice (grid,
                                       cr,
                                       element->embedded_elements);
    }

  return animate_spinner;
}
