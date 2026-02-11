III_hybrid (gfloat fsIn[SSLIMIT], gfloat tsOut[SSLIMIT], int sb, int ch,
    gr_info_t * gr_info, mp3tl * tl)
{
  gfloat rawout[36];
  int i;
  i = (gr_info->window_switching_flag && gr_info->mixed_block_flag &&
      (sb < 2)) ? 0 : gr_info->block_type;

  inv_mdct (fsIn, rawout, i);


#if defined(USE_ARM_VFP) && defined(__VFP_FP__) && !defined(__SOFTFP__)
  overlap_addition (tsOut, rawout, (gfloat *) tl->c_impl.prevblck[ch][sb]);
#elif defined(USE_LIBOIL)
  oil_add_f32 (tsOut, rawout, (gfloat *) tl->c_impl.prevblck[ch][sb], SSLIMIT);
  oil_memcpy (tl->c_impl.prevblck[ch][sb], rawout + 18,
      SSLIMIT * sizeof (gfloat));
#else
  for (i = 0; i < SSLIMIT; i++) {
    tsOut[i] = (gfloat) (rawout[i] + tl->c_impl.prevblck[ch][sb][i]);
    tl->c_impl.prevblck[ch][sb][i] = rawout[i + 18];
  }
#endif
}
