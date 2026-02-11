consider (JPL_Introduction *ii) {
  switch (ii->introduced ()->slice_type ()) {
  case JPL_ClassSlice::CS_OLD_BASE:
  case JPL_ClassSlice::CS_OLD_OTHER:
  case JPL_ClassSlice::CS_NORMAL:
#endif
    _unsorted.append (ii);
    return true;
  default:
    return false;
  }
}
