console_scroll_cb (GtkWidget *w, GdkEventKey *e, GtkWidget *t)
{
  GtkAdjustment *adj = gtk_tree_view_get_vadjustment (tree_view);
  gdouble value = adj->value;

  switch (e->state & GXINE_MODIFIER_MASK)
  {
  default:
    return FALSE;

  case 0:
    switch (e->keyval)
    {
    default:		return FALSE;
    case GDK_Page_Up:	value -= adj->page_increment; break;
    case GDK_Page_Down:	value += adj->page_increment; break;
    }
    break;

  case GDK_SHIFT_MASK:
    switch (e->keyval)
    {
    default:		return FALSE;
    case GDK_Up:	value -= adj->step_increment; break;
    case GDK_Down:	value += adj->step_increment; break;
    case GDK_Page_Up:	value -= adj->page_increment; break;
    case GDK_Page_Down:	value += adj->page_increment; break;
    }
    break;

  case GDK_CONTROL_MASK:
    switch (e->keyval)
    {
    default:		return FALSE;
    case GDK_Page_Up:	value = adj->lower; break;
    case GDK_Page_Down:	value = adj->upper; break;
    }
    break;
  }

  if (value < adj->lower)
    value = adj->lower;
  else if (value > adj->upper - adj->page_size)
    value = adj->upper - adj->page_size;

  gtk_adjustment_set_value (adj, value);
  return TRUE;
}
