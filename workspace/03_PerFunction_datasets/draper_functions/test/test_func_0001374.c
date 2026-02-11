go_option_menu_size_allocate (GtkWidget     *widget,
				    GtkAllocation *allocation)
{
  GtkWidget *child;
  GtkButton *button = GTK_BUTTON (widget);
  GtkAllocation child_allocation;
  GOOptionMenuProps props;
  gint border_width;

  go_option_menu_get_props (GO_OPTION_MENU (widget), &props);
  border_width = GTK_CONTAINER (widget)->border_width;

  widget->allocation = *allocation;
  if (GTK_WIDGET_REALIZED (widget))
    gdk_window_move_resize (button->event_window,
			    allocation->x + border_width, allocation->y + border_width,
			    allocation->width - border_width * 2, allocation->height - border_width * 2);

  child = GTK_BIN (widget)->child;
  if (child && GTK_WIDGET_VISIBLE (child))
    {
      gint xthickness = GTK_WIDGET (widget)->style->xthickness;
      gint ythickness = GTK_WIDGET (widget)->style->ythickness;

      child_allocation.x = widget->allocation.x + border_width + xthickness + props.focus_width + props.focus_pad + CHILD_LEFT_SPACING;
      child_allocation.y = widget->allocation.y + border_width + ythickness + props.focus_width + props.focus_pad + CHILD_TOP_SPACING;
      child_allocation.width = MAX (1, allocation->width - (border_width + xthickness + props.focus_width + props.focus_pad) * 2 -
				    props.indicator_size.width - props.indicator_spacing.left - props.indicator_spacing.right -
				    CHILD_LEFT_SPACING - CHILD_RIGHT_SPACING);
      child_allocation.height = MAX (1, allocation->height - (border_width + ythickness + props.focus_width + props.focus_pad) * 2 -
				     CHILD_TOP_SPACING - CHILD_BOTTOM_SPACING);

      if (gtk_widget_get_direction (GTK_WIDGET (widget)) == GTK_TEXT_DIR_RTL)
	child_allocation.x += props.indicator_size.width + props.indicator_spacing.left + props.indicator_spacing.right;

      gtk_widget_size_allocate (child, &child_allocation);
    }
}
