extend_selection (GtkCMCList      *clist,
		  GtkScrollType  scroll_type,
		  gfloat         position,
		  gboolean       auto_start_selection)
{
  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  if (clist_has_grab (clist) ||
      clist->selection_mode != GTK_SELECTION_MULTIPLE)
    return;

  if (auto_start_selection)
    set_anchor (clist, GTK_CMCLIST_ADD_MODE(clist), clist->focus_row,
		clist->focus_row);
  else if (clist->anchor == -1)
    return;

  move_focus_row (clist, scroll_type, position);

  if (ROW_TOP_YPIXEL (clist, clist->focus_row) + clist->row_height >
      clist->clist_window_height)
    gtk_cmclist_moveto (clist, clist->focus_row, -1, 1, 0);
  else if (ROW_TOP_YPIXEL (clist, clist->focus_row) < 0)
    gtk_cmclist_moveto (clist, clist->focus_row, -1, 0, 0);

  update_extended_selection (clist, clist->focus_row);
}
