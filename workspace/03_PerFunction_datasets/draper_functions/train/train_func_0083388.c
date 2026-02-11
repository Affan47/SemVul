rl_digit_loop ()
{
  int c, r;

  while (1)
    {
      if (_rl_arg_overflow ())
	return 1;

      c = _rl_arg_getchar ();

      if (c < 0)
	{
	  _rl_abort_internal ();
	  return -1;
	}

      r = _rl_arg_dispatch (_rl_argcxt, c);
      if (r <= 0 || (RL_ISSTATE (RL_STATE_NUMERICARG) == 0))
        break;
    }
}
