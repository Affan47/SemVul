lmc_handle_error_with_err_string(const char *ctx,
    const char *error_msg, const char* error_type, lmc_error_t *e) {
  if (!e) { return LMC_OK; }
  snprintf((char *)&e->error_str, 1023, "%s: %s", ctx, error_msg);
  snprintf((char *)&e->error_type, 1023, "%s", error_type);
  e->error_number = errno;
  return LMC_ERROR;
}
