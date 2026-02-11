cctx_prepare (pTHX)
{
  PL_top_env = &PL_start_env;

  if (cctx_current->flags & CC_TRACE)
    PL_runops = runops_trace;


  assert (("FATAL: can't prepare slf-less cctx in Coro module (please report)",
           slf_frame.prepare && PL_op->op_ppaddr == pp_slf));


  cctx_ssl_frame = slf_frame;

  slf_frame.prepare = slf_prepare_set_stacklevel;
  slf_frame.check   = slf_check_set_stacklevel;
}
