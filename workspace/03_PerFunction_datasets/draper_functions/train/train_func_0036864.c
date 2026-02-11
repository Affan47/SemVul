getline_n_unescape(FStream & in, DataPair & d, String & buf)
{
  if (!getline_n_unescape(in, buf, '\n')) return false;
  d.value.str  = buf.mstr();
  d.value.size = buf.size();
  return true;
}
