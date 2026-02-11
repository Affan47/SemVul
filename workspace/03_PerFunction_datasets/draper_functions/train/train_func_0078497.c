PyvtkEdgeBase_RichCompare(
  PyObject *o1, PyObject *o2, int opid)
{
  PyObject *n1 = NULL;
  PyObject *n2 = NULL;
  const vtkEdgeBase *so1 = NULL;
  const vtkEdgeBase *so2 = NULL;
  int result = -1;

  if (o1->ob_type == &PyvtkEdgeBase_Type)
    {
    PyVTKSpecialObject *s1 = (PyVTKSpecialObject *)o1;
    so1 = static_cast<const vtkEdgeBase *>(s1->vtk_ptr);
    }
  else
    {
    so1 = static_cast<const vtkEdgeBase *>(
      vtkPythonUtil::GetPointerFromSpecialObject(
        o1, "vtkEdgeBase", &n1));
    if (so1 == NULL)
      {
      PyErr_Clear();
      Py_INCREF(Py_NotImplemented);
      return Py_NotImplemented;
      }
    }

  if (o2->ob_type == &PyvtkEdgeBase_Type)
    {
    PyVTKSpecialObject *s2 = (PyVTKSpecialObject *)o2;
    so2 = static_cast<const vtkEdgeBase *>(s2->vtk_ptr);
    }
  else
    {
    so2 = static_cast<const vtkEdgeBase *>(
      vtkPythonUtil::GetPointerFromSpecialObject(
        o2, "vtkEdgeBase", &n2));
    if (so2 == NULL)
      {
      PyErr_Clear();
      Py_INCREF(Py_NotImplemented);
      return Py_NotImplemented;
      }
    }

  switch (opid)
    {
    case Py_LT:
      break;
    case Py_LE:
      break;
    case Py_EQ:
      result = ((*so1) == (*so2));
      break;
    case Py_NE:
      result = ((*so1) != (*so2));
      break;
    case Py_GT:
      break;
    case Py_GE:
      break;
    }

  if (n1)
    {
    Py_DECREF(n1);
    }
  else if (n2)
    {
    Py_DECREF(n2);
    }

  if (result == -1)
    {
    PyErr_SetString(PyExc_TypeError, (char *)"operation not available");
    return NULL;
    }

#if PY_VERSION_HEX >= 0x02030000

  return PyBool_FromLong((long)result);
#else
  if (result == 0)
    {
    Py_INCREF(Py_False);
    return Py_False;
    }
  Py_INCREF(Py_True);
  return Py_True;
#endif
}
