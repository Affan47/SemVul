PyVTKSpecialObject_SequenceString(PyObject *self)
{
  Py_ssize_t n, i;
  PyObject *s = NULL;
  PyObject *t, *o, *comma;
  const char *bracket = "[...]";

  if (self->ob_type->tp_as_sequence &&
      self->ob_type->tp_as_sequence->sq_item != NULL &&
      self->ob_type->tp_as_sequence->sq_ass_item == NULL)
    {
    bracket = "(...)";
    }

  i = Py_ReprEnter(self);
  if (i < 0)
    {
    return NULL;
    }
  else if (i > 0)
    {
    return PyString_FromString((char *)bracket);
    }

  n = PySequence_Size(self);
  if (n >= 0)
    {
    comma = PyString_FromString((char *)", ");
    s = PyString_FromStringAndSize((char *)bracket, 1);

    for (i = 0; i < n && s != NULL; i++)
      {
      if (i > 0)
        {
        PyString_Concat(&s, comma);
        }
      o = PySequence_GetItem(self, i);
      t = NULL;
      if (o)
        {
        t = PyObject_Repr(o);
        Py_DECREF(o);
        }
      if (t)
        {
        PyString_ConcatAndDel(&s, t);
        }
      else
        {
        Py_DECREF(s);
        s = NULL;
        }
      n = PySequence_Size(self);
      }

    if (s)
      {
      PyString_ConcatAndDel(&s,
        PyString_FromStringAndSize((char *)&bracket[4], 1));
      }

    Py_DECREF(comma);
    }

  Py_ReprLeave(self);

  return s;
}
