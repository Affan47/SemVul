set_gtk_entry_from_python_object(GtkWidget *entry, PyObject *args)
{
  const char *ss;

  if(!PyArg_ParseTuple(args, "s", &ss))
    return NULL;

  gtk_entry_set_text(GTK_ENTRY(entry), ss);

  Py_INCREF(Py_None);
  return Py_None;
}
