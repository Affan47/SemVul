cmd_listtrusted (assuan_context_t ctx, char *line)
{
  int rc;

  (void)line;

  rc = agent_listtrusted (ctx);
  if (rc)
    log_error ("command listtrusted failed: %s\n", gpg_strerror (rc));
  return rc;
}
