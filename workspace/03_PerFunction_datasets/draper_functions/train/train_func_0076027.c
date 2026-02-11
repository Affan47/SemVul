o_select_unselect_all(GSCHEM_TOPLEVEL *w_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  SELECTION *selection = toplevel->page_current->selection_list;
  GList *removed = NULL;
  GList *iter;

  removed = g_list_copy (geda_list_get_glist (selection));
  for (iter = removed; iter != NULL; iter = g_list_next (iter)) {
    o_selection_remove (toplevel, selection, (OBJECT *) iter->data);
  }


  if (removed != NULL) {
    g_run_hook_object_list (w_current, "%deselect-objects-hook", removed);
  }
}
