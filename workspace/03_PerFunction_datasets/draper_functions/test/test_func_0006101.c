showLabel(GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
  gpointer pt;
  gboolean visible;

  gtk_tree_model_get(model, iter, COLUMN_ELEMENT_POINTER_TO, &pt,
                     COLUMN_ELEMENT_VISIBLE, &visible, -1);
  DBG_fprintf(stderr, "VisuUi ElementCombobox: filter entry '%s' %p for model %p -> %d.\n",
              (GPOINTER_TO_INT(pt) != 0 &&
               GPOINTER_TO_INT(pt) != 1)?VISU_ELEMENT(pt)->name:"None", (gpointer)pt,
              (gpointer)model, (!pt && VISU_UI_ELEMENT_COMBOBOX(data)->hasNoneSelector) ||
              (pt && GPOINTER_TO_INT(pt) == 1 && VISU_UI_ELEMENT_COMBOBOX(data)->hasAllSelector) ||
              (pt && GPOINTER_TO_INT(pt) != 1 && visible));
  return (!pt && VISU_UI_ELEMENT_COMBOBOX(data)->hasNoneSelector) ||
    (pt && GPOINTER_TO_INT(pt) == 1 && VISU_UI_ELEMENT_COMBOBOX(data)->hasAllSelector) ||
    (pt && GPOINTER_TO_INT(pt) != 1 &&
     visible && (VISU_UI_ELEMENT_COMBOBOX(data)->showUnPhysical ||
                 visu_element_getPhysical(VISU_ELEMENT(pt))));
}
