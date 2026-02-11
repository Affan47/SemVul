build_transitive(PyObject * self, PyObject * args)
{
  PyObject * ret = NULL;
  PyObject * ab, * bc;
  char * seq1;
  char * seq2;
  float threshold;

  if (!PyArg_ParseTuple(args, "OOssf", &ab, &bc, &seq1, &seq2, &threshold)) {
    return NULL;
  }

  const ImmutableComparison * map_ab, * map_bc;
  map_ab = (const ImmutableComparison *) PyCObject_AsVoidPtr(ab);
  map_bc = (const ImmutableComparison *) PyCObject_AsVoidPtr(bc);

  try {
    ImmutableComparison * map_ac;
    { py_thread_saver save;

    map_ac = map_ab->build_transitive(*map_bc, seq1, seq2, threshold);

    }
    ret = PyCObject_FromVoidPtr(map_ac, cleanup_ImmComparison);
  } catch(paircomp_exception & e) {
    PyErr_SetString(PaircompParserError, e.error_msg.c_str());

    ret = NULL;
  }

  return ret;
}
