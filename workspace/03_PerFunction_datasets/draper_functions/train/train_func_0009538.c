dc()
{
  if (s_dc_owner != this) {
    if (s_dc_owner) {
      delete s_dc_owner->_dc;
      s_dc_owner->_dc = NULL;
    }
    s_dc_owner = this;
    _dc = (drawable) ? new FXDCWindow(drawable) : NULL;

    if (_dc)
      _dc->setLineCap(CAP_NOT_LAST);
  }
  return _dc;

}
