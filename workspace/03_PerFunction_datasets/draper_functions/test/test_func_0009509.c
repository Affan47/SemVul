Release() {
  drawable = 0;
  if (_dc) {
    delete _dc;
    _dc = 0;
    s_dc_owner = 0;
  }
  if (ppixmap)
    delete ppixmap;
  ppixmap = 0;
  x = 0;
  y = 0;
  createdDC = false;
  inited = false;
}
