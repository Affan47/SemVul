do_hashed_n_compare(PyObject * self, PyObject * args)
{
  PyObject * ret;
  char * top_seq, * bot_seq;
  unsigned int windowsize;
  float threshold;

  if (!PyArg_ParseTuple(args, "ssIf", &top_seq, &bot_seq, &windowsize,
			&threshold)) {
    return NULL;
  }

  ImmutableComparison * cmp;
  try {
    { py_thread_saver save;
    cmp = hashed_n_comparison(top_seq, bot_seq, windowsize, threshold);
    }

    ret = PyCObject_FromVoidPtr(cmp, cleanup_ImmComparison);
  } catch(paircomp_exception & e) {
    PyErr_SetString(PaircompAlgorithmsError, e.error_msg.c_str());

    ret = NULL;
  }

  return ret;
}
