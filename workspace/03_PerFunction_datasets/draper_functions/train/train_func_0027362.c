twitter_audit_log(THD *thd, enum enum_server_command command,
                       const char *query, uint query_length,
                       my_bool twitter_audit, void *acl)
{
  Security_context *sctx= thd->security_ctx;


  if (!opt_twitter_audit_log && !twitter_audit)
    return;


  if ((((sctx->master_access & GLOBAL_ACLS) != GLOBAL_ACLS) &&
       (sctx->master_access & IGNORE_LOGGING_ACL)) ||
      (thd->rli_slave && thd->rli_slave->sql_thd == thd))
  {
    return;
  }


  if (command == COM_CONNECT) {
    if (!acl || !twitter_audit_acl_check(acl))
      return;
  }

  logger.twitter_log_write(thd, command, query, query_length);
}
