uw_update_context (struct _Unwind_Context *context, _Unwind_FrameState *fs)
{
  uw_update_context_1 (context, fs);


  if (fs->signal_ra != 0)
    context->ra = (void *) fs->signal_ra;
  else
    context->ra = (void *) ((_Unwind_GetGR (context, fs->retaddr_column)
			     & XTENSA_RA_FIELD_MASK) | context->ra_high_bits);
}
