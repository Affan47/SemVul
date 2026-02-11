global_MODULE(command_t * self, global_t * global,
                                  char *data, apr_pool_t *ptmp) {
  apr_hash_t *blocks;

  while (*data == ' ') ++data;
  global->file_state = GLOBAL_FILE_STATE_MODULE;

  if (strcmp(data, "DEFAULT") == 0) {
    logger_log(global->logger, LOG_ERR, NULL,
               "Module name \"%s\" is not allowed", data);
    return APR_EINVAL;
  }

  if (!(blocks = apr_hash_get(global->modules, data, APR_HASH_KEY_STRING))) {
    blocks = apr_hash_make(global->pool);
    apr_hash_set(global->modules, data, APR_HASH_KEY_STRING, blocks);
  }

  global->blocks = blocks;

  return APR_SUCCESS;
}
