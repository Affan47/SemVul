_ds_add_attribute(config_t config, const char *key, const char *val) {
  attribute_t attr;

#ifdef VERBOSE
  LOGDEBUG("add attribute '%s' with value '%s'", key, val);
#endif

  attr = _ds_find_attribute(config, key);
  if (!attr) {
    int i;
    for(i=0;config[i];i++) { }
    config[i+1] = 0;
    config[i] = malloc(sizeof(struct attribute));
    if (!config[i]) {
      LOG(LOG_CRIT, ERR_MEM_ALLOC);
      return EUNKNOWN;
    }
    attr = config[i];
  } else {
    while(attr->next != NULL) {
      attr = attr->next;
    }
    attr->next = malloc(sizeof(struct attribute));
    if (!attr->next) {
      LOG(LOG_CRIT, ERR_MEM_ALLOC);
      return EUNKNOWN;
    }
    attr = attr->next;
  }
  attr->key = strdup(key);
  attr->value = strdup(val);
  attr->next = NULL;

  return 0;
}
