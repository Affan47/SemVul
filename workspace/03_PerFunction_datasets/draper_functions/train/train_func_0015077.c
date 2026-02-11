crypto_log_error(void)
{
  long err;
  char msg[1024];

  while ((err = ERR_get_error()) != 0) {
	ERR_error_string_n(err, msg, sizeof(msg));
	log_msg((LOG_ERROR_LEVEL, "%s", msg));
  }
}
