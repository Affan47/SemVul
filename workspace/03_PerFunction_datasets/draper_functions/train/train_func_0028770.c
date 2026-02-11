lam_ssi_crlam_self_checkpoint(void)
{
  pid_t pid;
  int status;


  if ((pid = fork()) < 0) {
    lam_perror("fork() in async handler");
    return LAMERROR;

  } else if (0 == pid) {


    lam_reset_pid_cache();
    if (kinit(PRCMD)) {


      lam_perror("kinit failed");
      kexit(1);
    }

    if (signal_app(cr_world, cr_world_n) != 0)
      kexit(1);

    if (lam_ssi_cr_verbose >= 40)
      lam_debug(lam_ssi_cr_did, "Child exiting\n");
    kexit(0);
  }


  if (lam_ssi_cr_verbose >= 40)
    lam_debug(lam_ssi_cr_did, "Parent waiting for pid %d\n", pid);

  if (waitpid(pid, &status, 0) != pid) {
    lam_perror("async_checkpoint waitpid");
    lam_debug(lam_ssi_cr_did, "waitpid(%d, ...) failed: %d",
        pid, errno);
    return LAMERROR;
  }

  if (lam_ssi_cr_verbose >= 40)
    lam_debug(lam_ssi_cr_did, "Parent reaped pid %d\n", pid);

  if ((WIFEXITED(status) != 0) && (WEXITSTATUS(status) != 0)) {
    lam_debug(lam_ssi_cr_did, "Bad exit status from child: %d.",
        WEXITSTATUS(status));
    return LAMERROR;
  }


  chkpnt_app_schema = create_app_schema(cr_world, cr_world_n);

  if (chkpnt_app_schema == NULL) {
    perror("create_app_schema");
    if (lam_ssi_cr_verbose >= 0)
      lam_debug(lam_ssi_cr_did, "Couldn't make app schema!");
    return LAMERROR;
  }

  return 0;
}
