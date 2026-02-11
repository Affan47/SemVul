SWIG_AsVal_unsigned_SS_int SWIG_TCL_DECL_ARGS_2(Tcl_Obj * obj, unsigned int *val)
{
  unsigned long v;
  int res = SWIG_AsVal_unsigned_SS_long SWIG_TCL_CALL_ARGS_2(obj, &v);
  if (SWIG_IsOK(res)) {
    if ((v > UINT_MAX)) {
      return SWIG_OverflowError;
    } else {
      if (val) *val = static_cast< unsigned int >(v);
    }
  }
  return res;
}
