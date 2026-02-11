redisCmd_exec(REDIS *redis, RedisCmd *cmd)
{
  bstr_t            rdata;
  RedisRetVal       *rv;
  int               rc;

  if (cmd->protocolString == NULL)
    if (redisCmd_buildProtocolStr(cmd) == NULL) return NULL;

  rc = _redis_send(redis, cmd->protocolString);
  if (rc != REDIS_NOERROR) return NULL;

  rdata = _redis_receive(redis);
  if (rdata == NULL) return NULL;
  rv = _redisRetVal_parse((char *)rdata, NULL);
  cmd->returnValue = rv;
  bstr_free(rdata);
  return rv;
}
