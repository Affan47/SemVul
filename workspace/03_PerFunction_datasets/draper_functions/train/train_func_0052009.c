_rl_arg_callback (cxt)
     _rl_arg_cxt cxt;
{
  int c, r;

  c = _rl_arg_getchar ();

  if (_rl_argcxt & NUM_READONE)
    {
      _rl_argcxt &= ~NUM_READONE;
      rl_restore_prompt ();
      rl_clear_message ();
      RL_UNSETSTATE(RL_STATE_NUMERICARG);
      rl_execute_next (c);
      return 0;
    }

  r = _rl_arg_dispatch (cxt, c);
  return (r != 1);
}
