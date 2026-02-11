real_undo_selection (GtkCMCList *clist)
{
  GList *work;

  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  if (clist_has_grab (clist) ||
      clist->selection_mode != GTK_SELECTION_MULTIPLE)
    return;

  GTK_CMCLIST_GET_CLASS (clist)->resync_selection (clist, NULL);

  if (!(clist->undo_selection || clist->undo_unselection))
    {
      gtk_cmclist_unselect_all (clist);
      return;
    }

  for (work = clist->undo_selection; work; work = work->next)
    g_signal_emit (G_OBJECT (clist), clist_signals[SELECT_ROW], 0,
		     GPOINTER_TO_INT (work->data), -1, NULL);

  for (work = clist->undo_unselection; work; work = work->next)
    {

      g_signal_emit (G_OBJECT (clist), clist_signals[UNSELECT_ROW], 0,
		       GPOINTER_TO_INT (work->data), -1, NULL);
    }

  if (gtk_widget_has_focus(GTK_WIDGET(clist)) && clist->focus_row != clist->undo_anchor)
    {
      gtk_cmclist_undraw_focus (GTK_WIDGET (clist));
      clist->focus_row = clist->undo_anchor;
      gtk_cmclist_draw_focus (GTK_WIDGET (clist));
    }
  else
    clist->focus_row = clist->undo_anchor;

  clist->undo_anchor = -1;

  g_list_free (clist->undo_selection);
  g_list_free (clist->undo_unselection);
  clist->undo_selection = NULL;
  clist->undo_unselection = NULL;

  if (ROW_TOP_YPIXEL (clist, clist->focus_row) + clist->row_height >
      clist->clist_window_height)
    gtk_cmclist_moveto (clist, clist->focus_row, -1, 1, 0);
  else if (ROW_TOP_YPIXEL (clist, clist->focus_row) < 0)
    gtk_cmclist_moveto (clist, clist->focus_row, -1, 0, 0);
}
