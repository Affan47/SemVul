operator==(const COMMON_COMPONENT& x)const
{
  const EVAL_BM_SFFM* p = dynamic_cast<const EVAL_BM_SFFM*>(&x);
  bool rv = p
    && _offset == p->_offset
    && _amplitude == p->_amplitude
    && _carrier == p->_carrier
    && _modindex == p->_modindex
    && _signal == p->_signal
    && _samples == p->_samples
    && _zero == p->_zero
    && _peak == p->_peak
    && EVAL_BM_ACTION_BASE::operator==(x);
  if (rv) {
    untested();
  }
  return rv;
}
