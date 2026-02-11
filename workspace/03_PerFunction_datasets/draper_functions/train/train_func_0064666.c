is_known_in_tunit (File *tunit) {
  int tunit_id = tunit->id ();
  if (_tunits.size () > 0)
    return _tunits.find (tunit_id) != _tunits.end ();
  for (SSet::const_iterator iter = source_locs ().begin ();
    iter != source_locs ().end (); ++iter) {
    int src_file_id = iter->file_id ();
    if (((File*)map (src_file_id))->is_known_in_tunit (tunit))
      return true;
  }
  return false;
}
