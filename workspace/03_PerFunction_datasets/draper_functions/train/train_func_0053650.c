PyVTKClass_Call(PyObject *op, PyObject *arg, PyObject *kw)
{
  PyVTKClass *self = (PyVTKClass *)op;
  static PyObject *initstr = 0;

  if (self->vtk_dict)
    {
    if (initstr == 0)
      {
      initstr = PyString_FromString("__init__");
      }

    PyObject *initfunc;
    initfunc = PyDict_GetItem(self->vtk_dict, initstr);

    if (initfunc)
      {
      PyObject *obj = PyVTKObject_New((PyObject *)self, NULL, NULL);
      PyObject *cinitfunc = PyObject_GetAttr(obj, initstr);
      PyObject *res = PyEval_CallObjectWithKeywords(cinitfunc, arg, kw);
      if (res == NULL)
        {
        Py_DECREF(obj);
        obj = NULL;
        }
      else if (res != Py_None)
        {
        PyErr_SetString(PyExc_TypeError, "__init__() should return None");
        Py_DECREF(obj);
        obj = NULL;
        }
      Py_DECREF(cinitfunc);
      return obj;
      }
    }

  if (kw != NULL)
    {
    PyErr_SetString(PyExc_TypeError,
                    "this function takes no keyword arguments");
    return NULL;
    }
  if (PyArg_ParseTuple(arg,(char*)""))
    {
    return PyVTKObject_New((PyObject *)self, NULL, NULL);
    }
  PyErr_Clear();
  if (PyArg_ParseTuple(arg,(char*)"O", &arg))
    {
    return vtkPythonUtil::GetObjectFromObject(
      arg, PyString_AsString(self->vtk_name));
    }
  PyErr_Clear();
  PyErr_SetString(PyExc_TypeError,
                  "function requires 0 or 1 arguments");

  return NULL;
}
