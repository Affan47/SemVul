local_infocard_auth(char *enc_xmlToken, char *aux, Ic_auth *ic_auth)
{
  int st;
  char *xmlToken;
  Ic_auth *ic;
  Ic_config *conf;
  Proc_lock *lock;
  Vfs_handle *h;

  if (enc_xmlToken == NULL || enc_xmlToken[0] == '\0')
	return(-1);

  if ((xmlToken = url_decode(enc_xmlToken, NULL, NULL)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Decode of xmlToken failed"));
	return(-1);
  }

  if ((lock = proc_lock_create(PROC_LOCK_INFOCARD)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Could not obtain lock"));
	return(-1);
  }

  st = -1;
  if ((h = vfs_open_item_type("infocards")) == NULL) {
	log_msg((LOG_ALERT_LEVEL, "Can't open item type \"infocards\""));
	goto done;
  }

  conf = ic_config();

  if ((conf->certfile = conf_val(CONF_INFOCARD_STS_CERTFILE)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "INFOCARD_STS_CERTFILE must be defined"));
	goto done;
  }

  if ((conf->keyfile = conf_val(CONF_INFOCARD_STS_KEYFILE)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "INFOCARD_STS_KEYFILE must be defined"));
	goto done;
  }

  conf->audience = ic_get_config_audience();
  conf->issuer = NULL;
  conf->enable_replay_detection = 0;
  conf->enable_signature_validation = 1;
  conf->max_token_size = 0;
  conf->max_drift_secs = 0;


  if ((ic = ic_lookup_entry(h, xmlToken, conf)) == NULL) {
	log_msg((LOG_DEBUG_LEVEL, "Lookup of InfoCard failed"));
	vfs_close(h);
	goto done;
  }
  log_msg((LOG_TRACE_LEVEL, "Found %s InfoCard",
		   (ic->type == IC_MANAGED_TYPE) ? "managed" : "self-issued"));
  log_msg((LOG_TRACE_LEVEL, "state=\"%s\", use_mode=\"%s\", username=\"%s\"",
		   (ic->state == IC_ENABLED) ? "enabled" : "disabled",
		   (ic->use_mode == IC_USE_MODE_DACS) ? "dacs"
		   : ((ic->use_mode == IC_USE_MODE_STATIC) ? "static" : "dynamic"),
		   ic->username));
  if (ic->roles != NULL)
	log_msg((LOG_TRACE_LEVEL, "roles=\"%s\"", ic->roles));

  if (vfs_close(h) == -1)
	log_msg((LOG_ERROR_LEVEL, "vfs_close() failed"));


  if (ic->state == IC_DISABLED) {
	log_msg((LOG_NOTICE_LEVEL, "Account is disabled for username \"%s\"",
			 ic->username));
	goto done;
  }
  else
	st = 0;

  *ic_auth = *ic;

 done:
  proc_lock_delete(lock);

  return(st);
}
