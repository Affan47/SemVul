gtktreeviewcolumn_gtk_tree_view_column_get_cell_renderers(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj tree_column_scm;
  GtkTreeViewColumn* tree_column;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-tree-view-column-get-cell-renderers");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  tree_column_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TREE_VIEW_COLUMN_P(tree_column_scm)) Scm_Error("<gtk-tree-view-column> required, but got %S", tree_column_scm);
  tree_column = SCM_GTK_TREE_VIEW_COLUMN(tree_column_scm);
  {
GList *lis = gtk_tree_view_column_get_cell_renderers(tree_column);
  ScmObj r = Scm_GoListToList(lis);
  g_list_free(lis);
  SCM_RETURN(r);
  }
}
