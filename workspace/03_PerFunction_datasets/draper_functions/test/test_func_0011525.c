read_VHDR(bgav_input_context_t * ctx, VHDR_t * ret)
  {
  if(!bgav_input_read_32_be(ctx, &ret->oneShotHiSamples) ||
     !bgav_input_read_32_be(ctx, &ret->repeatHiSamples) ||
     !bgav_input_read_32_be(ctx, &ret->samplesPerHiCycle) ||
     !bgav_input_read_16_be(ctx, &ret->samplesPerSec) ||
     !bgav_input_read_data(ctx, &ret->ctOctave, 1) ||
     !bgav_input_read_data(ctx, &ret->sCompression, 1) ||
     !bgav_input_read_32_be(ctx, &ret->volume))
    return 0;
#if 0
  dump_VHDR(ret);
#endif

  return 1;
  }
