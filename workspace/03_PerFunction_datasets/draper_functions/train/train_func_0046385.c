query1(Element *e, int port, int &chunk, int &offset) const
{
  int idx = e->eindex();
  if (idx < 0 || idx >= _elem_offset.size() || _elem_offset[idx] < 0
      || port >= _elem_icount[idx])
    return false;
  else {
    chunk = _chunks[ _elem_offset[idx] + port ];
    offset = _offsets[ _elem_offset[idx] + port ];
    return true;
  }
}
