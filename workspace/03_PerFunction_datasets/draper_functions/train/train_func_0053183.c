check_trustdb_stale(void)
{
  static int did_nextcheck=0;

  init_trustdb ();
  if (trustdb_args.no_trustdb)
    return;

  if (!did_nextcheck
      && (opt.trust_model==TM_PGP || opt.trust_model==TM_CLASSIC))
    {
      ulong scheduled;

      did_nextcheck = 1;
      scheduled = tdbio_read_nextcheck ();
      if ((scheduled && scheduled <= make_timestamp ())
	  || pending_check_trustdb)
        {
          if (opt.no_auto_check_trustdb)
            {
              pending_check_trustdb = 1;
              log_info (_("please do a --check-trustdb\n"));
            }
          else
            {
              log_info (_("checking the trustdb\n"));
              validate_keys (0);
            }
        }
    }
}
