run_shell (const char* pz_cmd)
{
  tSCC zNoServer[] = "Server not running, cannot run:\n%s\n\n";
  t_bool retry = BOOL_TRUE;

 do_retry:


  if (server_id == NULLPROCESS)
    {
      def_args[0] = find_shell ();

      server_id = proc2_fopen (&server_pair, def_args);
      if (server_id > 0)
        server_setup ();
    }


  if (server_id <= 0)
    {
      fprintf (stderr, zNoServer, pz_cmd);
      return XCNEW (char);
    }


  fprintf (server_pair.pf_write, "cd \"%s\"\n%s\n\necho\necho %s\n",
           p_cur_dir, pz_cmd, z_done);
  fflush (server_pair.pf_write);


  if (server_id == NULLPROCESS)
    {
      fprintf (stderr, zNoServer, pz_cmd);
      return XCNEW (char);
    }


  {
    char *pz = load_data (server_pair.pf_read);

    if (pz == (char *) NULL)
      {
	close_server ();

	if (retry)
	  {
	    retry = BOOL_FALSE;
	    goto do_retry;
	  }

        fprintf (stderr, "CLOSING SHELL SERVER - command failure:\n\t%s\n",
                 pz_cmd);
        pz = XCNEW (char);
      }
#ifdef DEBUG
    fprintf( stderr, "run_shell command success:  %s\n", pz );
#endif
    return pz;
  }
}
