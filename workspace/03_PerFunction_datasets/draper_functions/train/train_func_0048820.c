gtktreemodel_gtk_tree_model_get_iter(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj model_scm;
  GtkTreeModel* model;
  ScmObj path_scm;
  GtkTreePath* path;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-tree-model-get-iter");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  model_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TREE_MODEL_P(model_scm)) Scm_Error("<gtk-tree-model> required, but got %S", model_scm);
  model = SCM_GTK_TREE_MODEL(model_scm);
  path_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_TREE_PATH_P(path_scm)) Scm_Error("<gtk-tree-path> required, but got %S", path_scm);
  path = SCM_GTK_TREE_PATH(path_scm);
  {
GtkTreeIter iter; gboolean r;
    r= gtk_tree_model_get_iter(model, &iter, path);
    if (r) SCM_RETURN(SCM_MAKE_GTK_TREE_ITER(&iter));
    else SCM_RETURN(SCM_FALSE);
  }
}
