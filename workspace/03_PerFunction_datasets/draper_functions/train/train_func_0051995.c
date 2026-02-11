gdpy_convert_to_pyobj(const void* data, gd_type_t type)
{
  dtrace("%p, %02x", data, type);
  PyObject* pyobj = NULL;

  switch(type) {
    case GD_NULL:
      Py_INCREF(Py_None);
      pyobj = Py_None;
      break;
    case GD_UINT8:
      pyobj = PyInt_FromLong((long)*(uint8_t*)data);
      break;
    case GD_INT8:
      pyobj = PyInt_FromLong((long)*(int8_t*)data);
      break;
    case GD_UINT16:
      pyobj = PyInt_FromLong((long)*(uint16_t*)data);
      break;
    case GD_INT16:
      pyobj = PyInt_FromLong((long)*(int16_t*)data);
      break;
    case GD_UINT32:
      pyobj = PyLong_FromUnsignedLong((unsigned long)*(uint32_t*)data);
      break;
    case GD_INT32:
      pyobj = PyInt_FromLong((long)*(int32_t*)data);
      break;
    case GD_UINT64:
      pyobj = PyLong_FromUnsignedLongLong((unsigned long long)*(uint64_t*)data);
      break;
    case GD_INT64:
      pyobj = PyLong_FromLongLong((long long)*(int64_t*)data);
      break;
    case GD_FLOAT32:
      pyobj = PyFloat_FromDouble((double)*(float*)data);
      break;
    case GD_FLOAT64:
      pyobj = PyFloat_FromDouble(*(double*)data);
      break;
    case GD_COMPLEX64:
      pyobj = gdpy_from_complex((double complex)*(float complex*)data);
      break;
    case GD_COMPLEX128:
      pyobj = gdpy_from_complex(*(double complex*)data);
      break;
    case GD_UNKNOWN:
      break;
  }

  dreturn("%p", pyobj);
  return pyobj;
}
