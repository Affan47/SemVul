analysis_export(gchar *name)
{
struct model_pak *model;

model = sysenv.active_model;
g_assert(model != NULL);

dialog_destroy_type(FILE_SELECT);

if (model->graph_active)
  {
  graph_write(name, model->graph_active);
  gui_text_show(STANDARD, "Successfully exported graph.\n");
  }
else
  gui_text_show(WARNING, "Current model is not a graph.\n");
}
