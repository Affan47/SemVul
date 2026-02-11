p_hdf_obj_attr (PyObject *self, PyObject *args)
{
  HDFObject *ho = (HDFObject *)self;
  PyObject *rv, *item;
  HDF_ATTR *attr;

  rv = PyList_New(0);
  if (rv == NULL) return NULL;
  Py_INCREF(rv);
  attr = hdf_obj_attr (ho->data);
  while (attr != NULL)
  {
    item = Py_BuildValue("(s,s)", attr->key, attr->value);
    if (item == NULL)
    {
      Py_DECREF(rv);
      return NULL;
    }
    if (PyList_Append(rv, item) == -1)
    {
      Py_DECREF(rv);
      return NULL;
    }
    attr = attr->next;
  }
  return rv;
}
