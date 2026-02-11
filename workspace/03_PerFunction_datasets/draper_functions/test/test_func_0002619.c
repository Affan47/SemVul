wslay_frame_context_init(wslay_frame_context_ptr *ctx,
                             const struct wslay_frame_callbacks *callbacks,
                             void *user_data)
{
  *ctx = (wslay_frame_context_ptr)malloc(sizeof(struct wslay_frame_context));
  if(ctx == NULL) {
    return -1;
  }
  memset(*ctx, 0, sizeof(struct wslay_frame_context));
  (*ctx)->istate = RECV_HEADER1;
  (*ctx)->ireqread = 2;
  (*ctx)->ostate = PREP_HEADER;
  (*ctx)->user_data = user_data;
  (*ctx)->ibufmark = (*ctx)->ibuflimit = (*ctx)->ibuf;
  (*ctx)->callbacks = *callbacks;
  return 0;
}
