parse_env_error(const char *line)
{


  if (strlen(line) < (strlen(PROTO_ENV_ERROR) + 2))
    log_notice(LD_CONFIG, "Managed proxy sent us an %s without an error "
               "message.", PROTO_ENV_ERROR);

  log_warn(LD_CONFIG, "Managed proxy couldn't understand the "
           "pluggable transport environment variables. (%s)",
           line+strlen(PROTO_ENV_ERROR)+1);
}
