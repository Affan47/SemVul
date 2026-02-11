async_signal (void *signal_arg, int value)
{
  static char pipedata [8];

  async_t *async = (async_t *)signal_arg;
  int pending = async->pending;

  if (async->hysteresis)
    setsig (async->signum, SIG_IGN);

  *async->valuep = value ? value : 1;
  ECB_MEMORY_FENCE_RELEASE;
  async->pending = 1;
  ECB_MEMORY_FENCE_RELEASE;
  async_pending  = 1;
  ECB_MEMORY_FENCE_RELEASE;

  if (!async->blocked)
    {
      psig_pend [9]  = 1;
      ECB_MEMORY_FENCE_RELEASE;
      *sig_pending   = 1;
      ECB_MEMORY_FENCE_RELEASE;
    }

  if (!pending && async->fd_enable && async->ep.len)
    s_epipe_signal (&async->ep);
}
