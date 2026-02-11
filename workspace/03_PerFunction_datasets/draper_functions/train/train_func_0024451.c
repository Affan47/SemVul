PyVTKObject_Delete(PyObject *op)
{
  PyVTKObject *self = (PyVTKObject *)op;

#if PY_VERSION_HEX >= 0x02020000
  PyObject_GC_UnTrack(op);
#endif

#if PY_VERSION_HEX >= 0x02010000
  if (self->vtk_weakreflist != NULL)
    {
    PyObject_ClearWeakRefs(op);
    }
#endif


  vtkPythonUtil::RemoveObjectFromMap(op);

  Py_DECREF((PyObject *)self->vtk_class);
  Py_DECREF(self->vtk_dict);

#if PY_VERSION_HEX >= 0x02020000
  PyObject_GC_Del(op);
#elif PY_MAJOR_VERSION >= 2
  PyObject_Del(op);
#else
  PyMem_DEL(op);
#endif
}
