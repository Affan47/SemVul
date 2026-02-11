operator|=(const Alignment &o)
{
  if (_chunk == 0 || o._chunk < 0)
    return (*this = o);
  else if (_chunk <= 1 || o._chunk == 0)
    return *this;


  int new_chunk = _chunk, b = o._chunk;
  while (b) {
    int r = new_chunk % b;
    new_chunk = b;
    b = r;
  }


  int new_off1 = _offset % new_chunk;
  int new_off2 = o._offset % new_chunk;
  if (new_off1 == new_off2) {
    _chunk = new_chunk;
    _offset = new_off1;
    return *this;
  }


  int diff = new_off2 - new_off1;
  if (diff < 0)
      diff += new_chunk;
  if (diff > new_chunk / 2)
      diff = new_chunk - diff;
  if (new_chunk % diff == 0) {
    _chunk = diff;
    _offset = new_off1 % diff;
  } else {
    _chunk = 1;
    _offset = 0;
  }

  return *this;
}
