trigger(byte_t channel)
{
  byte_t c = channel & 3;

  if ((_control[c] & MODE) != MODE_COUNTER)
    return;

  _value[c]--;
  if (_value[c] > 0)
    return;

  _value[c] = _timer_value[c];
  try_trigger_irq(c);
}
