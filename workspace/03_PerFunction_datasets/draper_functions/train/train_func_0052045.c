select_show_prefs_internal (GNode *page, int exp)
{
  int state = 0;
  pref_t *item = page->data;
  pref_t *parent = page->parent ? page->parent->data : NULL;
  GNode *child;

  if (parent && parent->notebook == GINT_TO_POINTER (1))
    return 0;

  child = g_node_first_child (page);

  if (PREF_T(child)->notebook)
  {

    GtkNotebook *notebook = GTK_NOTEBOOK(item->page.notebook);
    while (gtk_notebook_get_n_pages (notebook))
      gtk_notebook_remove_page (notebook, 0);
    for (; child; child = g_node_next_sibling (child))
      state |= select_show_prefs_internal (child, exp);
  }
  else
  {

    pref_item_t *last = NULL;
    for (; child; child = g_node_next_sibling (child))
    {
      pref_item_t *pref = child->data;
      void (*func)(GtkWidget *);
      if (pref->exp <= exp)
      {
	func = gtk_widget_show;
	state |= 1;
	last = pref;
      }
      else
      {
	func = gtk_widget_hide;
	state |= 2;
      }
      if (pref->exp <= exp)
	last = pref;
      func (pref->todefault);
      func (pref->revert);
      func (pref->editable);
      func (pref->label);
      func (pref->separator);
    }
    if (last)
      gtk_widget_hide (last->separator);
  }


  if (parent && state != 2)
    gtk_notebook_append_page (GTK_NOTEBOOK(parent->notebook), item->page.page,
			      gtk_label_new (item->page.label));

  return state;
}
