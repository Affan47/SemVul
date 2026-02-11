reset(bool power_on)
{
  int a;

  _irq_vector = 0;
  for (a = 0;a < 4;a++)
    {
      _control[a]     = 0x23;
      _value[a]       = 0;
      _restart[a]     = 0;
      _timer_value[a] = 0;
      _irq_active[a]  = 0;
      _irq_pending[a] = 0;
      _irq_valid[a]   += 4;
    }
}
