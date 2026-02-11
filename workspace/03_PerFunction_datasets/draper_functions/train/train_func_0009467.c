go_option_menu_size_request (GtkWidget      *widget,
				   GtkRequisition *requisition)
{
  GOOptionMenu *option_menu = GO_OPTION_MENU (widget);
  GOOptionMenuProps props;
  gint tmp;
  GtkRequisition child_requisition = { 0, 0 };

  go_option_menu_get_props (option_menu, &props);

  if (GTK_BIN (option_menu)->child && GTK_WIDGET_VISIBLE (GTK_BIN (option_menu)->child))
    {
      gtk_widget_size_request (GTK_BIN (option_menu)->child, &child_requisition);

      requisition->width += child_requisition.width;
      requisition->height += child_requisition.height;
    }

  requisition->width = ((GTK_CONTAINER (widget)->border_width +
			 GTK_WIDGET (widget)->style->xthickness + props.focus_pad) * 2 +
			MAX (child_requisition.width, option_menu->width) +
 			props.indicator_size.width +
 			props.indicator_spacing.left + props.indicator_spacing.right +
			CHILD_LEFT_SPACING + CHILD_RIGHT_SPACING + props.focus_width * 2);
  requisition->height = ((GTK_CONTAINER (widget)->border_width +
			  GTK_WIDGET (widget)->style->ythickness + props.focus_pad) * 2 +
			 MAX (child_requisition.height, option_menu->height) +
			 CHILD_TOP_SPACING + CHILD_BOTTOM_SPACING + props.focus_width * 2);

  tmp = (requisition->height - MAX (child_requisition.height, option_menu->height) +
	 props.indicator_size.height + props.indicator_spacing.top + props.indicator_spacing.bottom);
  requisition->height = MAX (requisition->height, tmp);
}
