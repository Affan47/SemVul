mic_read_entry(Vfs_handle *h, char *key)
{
  char *stored_entry;
  Mic_entry *mic;

  log_msg((LOG_TRACE_LEVEL, "Fetch key=\"%s\"", key));
  if (vfs_get(h, key, (void **) &stored_entry, NULL) == -1) {
	log_msg((LOG_ERROR_LEVEL, "Cannot read entry for key \"%s\"", key));
	return(NULL);
  }

  if ((mic = mic_parse_entry(stored_entry)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Cannot decode record, key \"%s\"", key));
	return(NULL);
  }

  return(mic);
}
