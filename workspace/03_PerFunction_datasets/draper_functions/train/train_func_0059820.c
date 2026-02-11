goo_canvas_path_model_finalize (GObject *object)
{
  GooCanvasPathModel *pmodel = (GooCanvasPathModel*) object;

  if (pmodel->path_data.path_commands)
    g_array_free (pmodel->path_data.path_commands, TRUE);

  G_OBJECT_CLASS (goo_canvas_path_model_parent_class)->finalize (object);
}
