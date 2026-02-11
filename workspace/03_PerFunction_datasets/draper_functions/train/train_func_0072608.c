lam_ssi_crmpi_self_init(void)
{
  lt_dlhandle executable;
  int do_restart = 0;


  executable = lt_dlopen(NULL);
  if (executable == NULL) {
    lam_perror("opening ltdl\n");
    return NULL;
  }


  user_checkpoint_fn = find_function(executable, param_checkpoint_name,
				     "checkpoint");
  user_continue_fn = find_function(executable, param_continue_name,
				   "continue");
  user_restart_fn = find_function(executable, param_restart_name,
				  "restart");


  lt_dlclose(executable);

  do_restart = lam_ssi_base_param_lookup_int(param_do_restart);

  if (1 == do_restart) {
      lam_debug(lam_ssi_cr_did,
                "self:thread:%d: do_restart == 1",
                getpid());
      if (user_restart_fn != NULL) {
          lam_debug(lam_ssi_cr_did,
                    "self:thread:%d: calling user restart function",
                    getpid());
          if (lam_ssi_base_mpi_init_callback(user_restart_fn) != MPI_SUCCESS) {
              return NULL;
          }
      } else {
          lam_debug(lam_ssi_cr_did,
                    "self:thread:%d: WARNING: no user restart function found; skipped",
                    getpid());
      }
  }


  if (pipe(crmpi_self_filedesc) != 0) {
    show_help_file("lam-ssi-crmpi-self-helpfile", "cr-self-init",
		   "pipe-creation-fail", NULL);
    return NULL;
  }

  lam_ssi_crmpi_base_init_lock();


  if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
    show_help_file("lam-ssi-crmpi-self-helpfile", "cr-self-init",
		    "pipe-creation-fail", NULL);

    close(crmpi_self_filedesc[0]);
    close(crmpi_self_filedesc[1]);
    return NULL;
 }


  if (lam_thread_create(&crmpi_self_thread, thread_handler, 0) != 0) {
    show_help_file("lam-ssi-crmpi-self-helpfile", "cr-self-init",
		   "thread-creation-fail", NULL);

    close(crmpi_self_filedesc[0]);
    close(crmpi_self_filedesc[1]);
    return NULL;
  }


  return (&module_actions);
}
