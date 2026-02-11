_wrap_FloatList___setitem__(PyObject *self, PyObject *args) {
  int argc;
  PyObject *argv[4];
  int ii;

  if (!PyTuple_Check(args)) SWIG_fail;
  argc = args ? (int)PyObject_Length(args) : 0;
  for (ii = 0; (ii < 3) && (ii < argc); ii++) {
    argv[ii] = PyTuple_GET_ITEM(args,ii);
  }
  if (argc == 2) {
    int _v;
    int res = swig::asptr(argv[0], (std::vector<double,std::allocator< double > >**)(0));
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        _v = PySlice_Check(argv[1]);
      }
      if (_v) {
        return _wrap_FloatList___setitem____SWIG_1(self, args);
      }
    }
  }
  if (argc == 3) {
    int _v;
    int res = swig::asptr(argv[0], (std::vector<double,std::allocator< double > >**)(0));
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        _v = PySlice_Check(argv[1]);
      }
      if (_v) {
        int res = swig::asptr(argv[2], (std::vector<double,std::allocator< double > >**)(0));
        _v = SWIG_CheckState(res);
        if (_v) {
          return _wrap_FloatList___setitem____SWIG_0(self, args);
        }
      }
    }
  }
  if (argc == 3) {
    int _v;
    int res = swig::asptr(argv[0], (std::vector<double,std::allocator< double > >**)(0));
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        int res = SWIG_AsVal_ptrdiff_t(argv[1], NULL);
        _v = SWIG_CheckState(res);
      }
      if (_v) {
        {
          int res = SWIG_AsVal_double(argv[2], NULL);
          _v = SWIG_CheckState(res);
        }
        if (_v) {
          return _wrap_FloatList___setitem____SWIG_2(self, args);
        }
      }
    }
  }

fail:
  SWIG_SetErrorMsg(PyExc_NotImplementedError,"Wrong number or type of arguments for overloaded function 'FloatList___setitem__'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    std::vector< double >::__setitem__(PySliceObject *,std::vector< double,std::allocator< double > > const &)\n"
    "    std::vector< double >::__setitem__(PySliceObject *)\n"
    "    std::vector< double >::__setitem__(std::vector< double >::difference_type,std::vector< double >::value_type const &)\n");
  return 0;
}
