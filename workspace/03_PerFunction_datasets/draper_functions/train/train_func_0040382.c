free_variable_item (gpointer data)
{
  ClassBrowserVar *var=(ClassBrowserVar *)data;
  if (var->varname) g_free(var->varname);
  if (var->functionname) g_free(var->functionname);
  if (var->filename) g_free(var->filename);
  if (var) g_slice_free(ClassBrowserVar, var);
}
