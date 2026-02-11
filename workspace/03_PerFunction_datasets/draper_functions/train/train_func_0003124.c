tr_review(COMPONENT* d)
{
  double time = d->_sim->_time0;
  time += d->_sim->_dtmin * .01;
  double raw_time = time;

  if (0 < _period && _period < BIGBIG) {
    if (time > _delay) {
      time = fmod(time - _delay, _period) + _delay;
    }else{
    }
  }else{
  }
  double time_offset = raw_time - time;

  if (time >= _delay+_rise+_width+_fall) {
    d->_time_by.min_event(_delay + _period + time_offset);
  }else if (time >= _delay+_rise+_width) {
    d->_time_by.min_event(_delay + _rise + _width + _fall + time_offset);
  }else if (time >= _delay + _rise) {
    d->_time_by.min_event(_delay + _rise + _width + time_offset);
  }else if (time >= _delay) {
    d->_time_by.min_event(_delay + _rise + time_offset);
  }else{
    d->_time_by.min_event(_delay + time_offset);
  }

  return d->_time_by;
}
