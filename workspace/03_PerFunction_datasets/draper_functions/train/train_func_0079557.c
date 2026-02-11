pygi_source_scanner_append_filename (PyGISourceScanner *self,
				     PyObject          *args)
{
  char *filename;
  GFile *file;

  if (!PyArg_ParseTuple (args, "s:SourceScanner.append_filename", &filename))
    return NULL;

  file = g_file_new_for_path (filename);
  g_hash_table_add (self->scanner->files, file);

  Py_INCREF (Py_None);
  return Py_None;
}
