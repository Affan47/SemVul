SWIG_Tcl_Disown(void *ptr) {
  Tcl_HashEntry *entryPtr = Tcl_FindHashEntry(SWIG_Tcl_ObjectTable(), (char *) ptr);
  if (entryPtr) {
    Tcl_DeleteHashEntry(entryPtr);
    return 1;
  }
  return 0;
}
