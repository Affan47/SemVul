_gcry_fips_is_operational (void)
{
  int result;

  if (!fips_mode ())
    result = 1;
  else
    {
      lock_fsm ();
      if (current_state == STATE_INIT)
        {


          unlock_fsm ();
          _gcry_fips_run_selftests (0);
          lock_fsm ();
        }

      result = (current_state == STATE_OPERATIONAL);
      unlock_fsm ();
    }
  return result;
}
