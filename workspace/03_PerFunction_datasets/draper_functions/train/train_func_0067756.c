slf_init_pool_handler (pTHX_ struct CoroSLF *frame, CV *cv, SV **arg, int items)
{
  HV *hv = (HV *)SvRV (coro_current);
  struct coro *coro = SvSTATE_hv ((SV *)hv);

  if (ecb_expect_true (coro->saved_deffh))
    {

      SvREFCNT_dec ((SV *)PL_defoutgv); PL_defoutgv = (GV *)coro->saved_deffh;
      coro->saved_deffh = 0;

      if (coro_rss (aTHX_ coro) > SvUV (sv_pool_rss)
          || av_len (av_async_pool) + 1 >= SvIV (sv_pool_size))
        {
          slf_init_terminate_cancel_common (aTHX_ frame, hv);
          return;
        }
      else
        {
          av_clear (GvAV (PL_defgv));
          hv_store (hv, "desc", sizeof ("desc") - 1, SvREFCNT_inc_NN (sv_async_pool_idle), 0);

          coro->prio = 0;

          if (coro->cctx && (coro->cctx->flags & CC_TRACE))
            api_trace (aTHX_ coro_current, 0);

          frame->prepare = prepare_schedule;
          av_push (av_async_pool, SvREFCNT_inc (hv));
        }
    }
  else
    {

      frame->prepare = prepare_nop;
    }

  frame->check = slf_check_pool_handler;
  frame->data  = (void *)coro;
}
