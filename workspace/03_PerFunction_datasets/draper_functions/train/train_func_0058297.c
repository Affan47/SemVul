wslay_event_want_write(wslay_event_context_ptr ctx)
{
  return ctx->write_enabled &&
    (!wslay_queue_empty(ctx->send_queue) ||
     !wslay_queue_empty(ctx->send_ctrl_queue) || ctx->omsg);
}
