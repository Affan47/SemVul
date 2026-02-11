calc_attrs_length(PyObject *attributes, int indent,
			     int self_indent)
{
  int attr_length = 0;
  int i;

  if (indent == -1)
    return -1;

  for (i = 0; i < PyList_Size (attributes); ++i)
    {
      PyObject *tuple, *pyvalue;
      PyObject *s = NULL;
      char *attr, *value;
      char *escaped;

      tuple = PyList_GetItem (attributes, i);
      if (PyTuple_GetItem(tuple, 1) == Py_None)
	continue;

      if (!PyArg_ParseTuple(tuple, "sO", &attr, &pyvalue))
        return -1;

      if (PyUnicode_Check(pyvalue)) {
        s = PyUnicode_AsUTF8String(pyvalue);
        if (!s) {
          return -1;
        }
        value = PyString_AsString(s);
      } else if (PyString_Check(pyvalue)) {
        value = PyString_AsString(pyvalue);
      } else {
        PyErr_SetString(PyExc_TypeError,
                        "value must be string or unicode");
        return -1;
      }

      escaped = g_markup_escape_text (value, -1);
      attr_length += 2 + strlen(attr) + strlen(escaped) + 2;
      g_free(escaped);
      Py_XDECREF(s);
    }

  return attr_length + indent + self_indent;
}
