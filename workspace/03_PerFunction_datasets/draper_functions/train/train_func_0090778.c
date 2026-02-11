default_token_replay_detector(Icx_ctx *ctx, const xmlChar *replay_string,
							  time_t not_on_or_after, void *detector_context)
{

  if (ctx->validate_token_replay) {
	log_msg((LOG_ERROR_LEVEL, "Default token replay detection fails"));
	return(1);
  }

  log_msg((LOG_ERROR_LEVEL, "Default token replay detection ok"));
  return(0);
}
