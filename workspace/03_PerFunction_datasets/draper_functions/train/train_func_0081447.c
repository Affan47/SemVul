put(unsigned int new_value)
{

  unsigned int new_IRCF = (new_value & ( IRCF0 | IRCF1 | IRCF2)) >> 4;
  unsigned int old_IRCF = (value.get() & ( IRCF0 | IRCF1 | IRCF2)) >> 4;
  trace.raw(write_trace.get() | value.get());
  value.put(new_value);

  if (set_rc_frequency())
  {
	if (old_IRCF == 0 && new_IRCF != 0)
	{
	    guint64 settle;

	    settle = (guint64) (get_cycles().instruction_cps() * 4e-3);
	    get_cycles().set_break(get_cycles().get() + settle, this);
	    new_value &= ~ IOFS;
	}
	else
	    new_value |= IOFS;
  }
}
