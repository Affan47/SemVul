worker_process(ESL_GETOPTS *go)
{
  HMMD_COMMAND *cmd      = NULL;
  int           shutdown = 0;
  WORKER_ENV    env;
  int           status;


  impl_Init();
  p7_FLogsumInit();

  if (esl_opt_IsOn(go, "--cpu")) env.ncpus = esl_opt_GetInteger(go, "--cpu");
  else esl_threads_CPUCount(&env.ncpus);

  env.hmm_db = NULL;
  env.seq_db = NULL;
  env.fd     = setup_masterside_comm(go);

  while (!shutdown)
    {
      if ((status = read_Command(&cmd, &env)) != eslOK) break;

      switch (cmd->hdr.command) {
      case HMMD_CMD_INIT:      process_InitCmd  (cmd, &env);                break;
      case HMMD_CMD_SCAN:      process_SearchCmd(cmd, &env);                break;
      case HMMD_CMD_SEARCH:    process_SearchCmd(cmd, &env);                break;
      case HMMD_CMD_SHUTDOWN:  process_Shutdown (cmd, &env);  shutdown = 1; break;
      default: p7_syslog(LOG_ERR,"[%s:%d] - unknown command %d (%d)\n", __FILE__, __LINE__, cmd->hdr.command, cmd->hdr.length);
      }

      free(cmd);
      cmd = NULL;
    }

  if (env.hmm_db) p7_hmmcache_Close(env.hmm_db);
  if (env.seq_db) p7_seqcache_Close(env.seq_db);
  if (env.fd != -1) close(env.fd);
  return;
}
