gtktreemodel_gtk_tree_path_get_indices(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj path_scm;
  GtkTreePath* path;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-tree-path-get-indices");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  path_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TREE_PATH_P(path_scm)) Scm_Error("<gtk-tree-path> required, but got %S", path_scm);
  path = SCM_GTK_TREE_PATH(path_scm);
  {
int depth = gtk_tree_path_get_depth(path);
    int *r = gtk_tree_path_get_indices(path), i;
    ScmObj h = SCM_NIL, t = SCM_NIL;
    for (i=0; i<depth; i++) {
      SCM_APPEND1(h, t, Scm_MakeInteger(r[i]));
    }
    SCM_RETURN(h);
  }
}
