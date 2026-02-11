c_out(byte_t channel, byte_t val)
{
  if ((_control[channel] & CONSTANT) == CONSTANT_LOAD)
    {
      _control[channel] &= ~(CONSTANT | RESET);
      run_cb_start(channel);

      if ((_control[channel] & MODE) == MODE_TIMER)
	{
	  if ((_control[channel] & PRESCALER) == PRESCALER_16)
	    {
	      _timer_value[channel] = val << 4;
	      if (_timer_value[channel] == 0)
		_timer_value[channel] = 4096;
	    }
	  else
	    {
	      _timer_value[channel] = val << 8;


	      if (_timer_value[channel] == 0)
		_timer_value[channel] = 65535;
	    }
	}
      else
	{


	  _timer_value[channel] = val;
	}

      _counter[channel] = get_counter();
      _value[channel] = _timer_value[channel];
      run_cb_tc(channel, _timer_value[channel]);

      if ((_control[channel] & MODE) == MODE_COUNTER)
	{
	  handle_counter_mode(channel);
	  return;
        }

      _irq_valid[channel] += 4;


      add_callback(_timer_value[channel] + 4, this, (void *)((long)_irq_valid[channel]));
      return;
    }

  if ((val & CONTROL) == CONTROL_VECTOR)
    {
      if (channel != 0) return;
      _irq_vector = val & ~ 7;
      return;
    }

  if ((val & RESET) == RESET_ACTIVE)
    {
      _value[channel] = _timer_value[channel];
      _irq_valid[channel] += 4;
      if ((_control[channel] & RESET) != RESET_ACTIVE)
	run_cb_stop(channel);
    }

  _control[channel] = val;
}
