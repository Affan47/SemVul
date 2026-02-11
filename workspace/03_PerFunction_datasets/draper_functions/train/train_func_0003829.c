_wrap_PDFSetInfoList___getitem__(PyObject *self, PyObject *args) {
  int argc;
  PyObject *argv[3];
  int ii;

  if (!PyTuple_Check(args)) SWIG_fail;
  argc = args ? (int)PyObject_Length(args) : 0;
  for (ii = 0; (ii < 2) && (ii < argc); ii++) {
    argv[ii] = PyTuple_GET_ITEM(args,ii);
  }
  if (argc == 2) {
    int _v;
    int res = swig::asptr(argv[0], (std::vector<LHAPDF::PDFSetInfo,std::allocator< LHAPDF::PDFSetInfo > >**)(0));
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        _v = PySlice_Check(argv[1]);
      }
      if (_v) {
        return _wrap_PDFSetInfoList___getitem____SWIG_0(self, args);
      }
    }
  }
  if (argc == 2) {
    int _v;
    int res = swig::asptr(argv[0], (std::vector<LHAPDF::PDFSetInfo,std::allocator< LHAPDF::PDFSetInfo > >**)(0));
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        int res = SWIG_AsVal_ptrdiff_t(argv[1], NULL);
        _v = SWIG_CheckState(res);
      }
      if (_v) {
        return _wrap_PDFSetInfoList___getitem____SWIG_1(self, args);
      }
    }
  }

fail:
  SWIG_SetErrorMsg(PyExc_NotImplementedError,"Wrong number or type of arguments for overloaded function 'PDFSetInfoList___getitem__'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    std::vector< LHAPDF::PDFSetInfo >::__getitem__(PySliceObject *)\n"
    "    std::vector< LHAPDF::PDFSetInfo >::__getitem__(std::vector< LHAPDF::PDFSetInfo >::difference_type) const\n");
  return 0;
}
