get_layout_location (EelEditableLabel  *label,
                     gint      *xp,
                     gint      *yp)
{
  GtkMisc *misc;
  GtkWidget *widget;
  gfloat xalign, yalign;
  GtkRequisition req;
  gint x, y, xpad, ypad;
  GtkAllocation allocation;

  misc = GTK_MISC (label);
  widget = GTK_WIDGET (label);
  gtk_misc_get_alignment (misc, &xalign, &yalign);

  if (gtk_widget_get_direction (widget) != GTK_TEXT_DIR_LTR)
    xalign = 1.0 - xalign;

  gtk_widget_get_preferred_size (widget, &req, NULL);
  gtk_misc_get_padding (misc, &xpad, &ypad);

  gtk_widget_get_allocation (widget, &allocation);
  x = floor (xpad
             + ((allocation.width - req.width) * xalign)
             + 0.5);

  y = floor (ypad
             + ((allocation.height - req.height) * yalign)
             + 0.5);

  if (xp)
    *xp = x;

  if (yp)
    *yp = y;
}
