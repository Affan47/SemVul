py_gc_sound_policy_set(PyObject* self, PyObject* args)
{
  guint policy;

  if(!PyArg_ParseTuple(args, "i:gc_sound_policy_set",&policy))
    return NULL;


  gc_sound_policy_set(policy);


  Py_INCREF(Py_None);
  return Py_None;
}
