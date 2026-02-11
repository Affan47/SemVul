SWIG_AsCharArray(PyObject * obj, char *val, size_t size)
{
  char* cptr = 0; size_t csize = 0; int alloc = SWIG_OLDOBJ;
  int res = SWIG_AsCharPtrAndSize(obj, &cptr, &csize, &alloc);
  if (SWIG_IsOK(res)) {
    if ((csize == size + 1) && cptr && !(cptr[csize-1])) --csize;
    if (csize <= size) {
      if (val) {
	if (csize) memcpy(val, cptr, csize*sizeof(char));
	if (csize < size) memset(val + csize, 0, (size - csize)*sizeof(char));
      }
      if (alloc == SWIG_NEWOBJ) {
	delete[] cptr;
	res = SWIG_DelNewMask(res);
      }
      return res;
    }
    if (alloc == SWIG_NEWOBJ) delete[] cptr;
  }
  return SWIG_TypeError;
}
