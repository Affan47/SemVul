GetObjectFromObject(
  PyObject *arg, const char *type)
{
  union vtkPythonUtilPointerUnion u;

  if (PyString_Check(arg))
    {
    vtkObjectBase *ptr;
    char *ptrText = PyString_AsString(arg);

    char typeCheck[1024];
#if VTK_SIZEOF_VOID_P == VTK_SIZEOF_LONG
    int i = sscanf(ptrText,"_%lx_%s", &u.l, typeCheck);
#elif defined(VTK_TYPE_USE_LONG_LONG)
    int i = sscanf(ptrText,"_%llx_%s", &u.l, typeCheck);
#elif defined(VTK_TYPE_USE___INT64)
    int i = sscanf(ptrText,"_%I64x_%s", &u.l, typeCheck);
#endif

    if (i <= 0)
      {
#if VTK_SIZEOF_VOID_P == VTK_SIZEOF_LONG
      i = sscanf(ptrText,"Addr=0x%lx", &u.l);
#elif defined(VTK_TYPE_USE_LONG_LONG)
      i = sscanf(ptrText,"Addr=0x%llx", &u.l);
#elif defined(VTK_TYPE_USE___INT64)
      i = sscanf(ptrText,"Addr=0x%I64x", &u.l);
#endif
      }
    if (i <= 0)
      {
      i = sscanf(ptrText, "%p", &u.p);
      }
    if (i <= 0)
      {
      PyErr_SetString(PyExc_ValueError, "could not extract hexidecimal address from argument string");
      return NULL;
      }

    ptr = static_cast<vtkObjectBase *>(u.p);

    if (!ptr->IsA(type))
      {
      char error_string[2048];
      sprintf(error_string,"method requires a %.500s address, a %.500s address was provided.",
              type, ptr->GetClassName());
      PyErr_SetString(PyExc_TypeError, error_string);
      return NULL;
      }

    return vtkPythonUtil::GetObjectFromPointer(ptr);
    }

  PyErr_SetString(PyExc_TypeError, "method requires a string argument");
  return NULL;
}
