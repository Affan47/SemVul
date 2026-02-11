_wrap_ConstIterator___sub__(int nargs, VALUE *args, VALUE self) {
  int argc;
  VALUE argv[3];
  int ii;

  argc = nargs + 1;
  argv[0] = self;
  if (argc > 3) SWIG_fail;
  for (ii = 1; (ii < argc); ++ii) {
    argv[ii] = args[ii-1];
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_swig__ConstIterator, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_swig__ConstIterator, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_ConstIterator___sub____SWIG_1(nargs, args, self);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_swig__ConstIterator, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        int res = SWIG_AsVal_ptrdiff_t(argv[1], NULL);
        _v = SWIG_CheckState(res);
      }
      if (_v) {
        return _wrap_ConstIterator___sub____SWIG_0(nargs, args, self);
      }
    }
  }

fail:
  Ruby_Format_OverloadedError( argc, 3, "__sub__.new",
    "    __sub__.new(ptrdiff_t n)\n"
    "    __sub__.new(swig::ConstIterator const &x)\n");

  return Qnil;
}
