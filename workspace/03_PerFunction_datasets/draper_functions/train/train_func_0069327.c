dc_advance()
{
  assert(_sim->_time0 == 0.);

  for (int i=OPT::_keep_time_steps-1; i>=0; --i) {
    assert(_time[i] == 0.);
  }

  _dt = NOT_VALID;
}
