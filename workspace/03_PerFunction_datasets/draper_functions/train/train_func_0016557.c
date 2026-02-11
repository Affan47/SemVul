II_dequant_and_scale_sample (guint sample[2][3][SBLIMIT],
    guint bit_alloc[2][SBLIMIT], float fraction[2][3][SBLIMIT],
    guint scale_index[2][3][SBLIMIT], int scale_block, frame_params * fr_ps)
{
  int sb, gr, ch, x;
  int stereo = fr_ps->stereo;
  int sblimit = fr_ps->sblimit;
  const al_table *alloc = fr_ps->alloc;

  for (sb = 0; sb < sblimit; sb++) {
    for (ch = 0; ch < stereo; ch++) {
      guint allocation = bit_alloc[ch][sb];

      if (allocation != 0) {
        gfloat scale_val, val;
        gfloat c_quant, d_quant;

        c_quant = c[alloc[0][sb][allocation].quant];
        d_quant = d[alloc[0][sb][allocation].quant];
        scale_val = (gfloat) multiple[scale_index[ch][scale_block][sb]];

        for (gr = 0; gr < 3; gr++) {

          x = 0;
          while ((1UL << x) < (*alloc)[sb][allocation].steps)
            x++;


          if (((sample[ch][gr][sb] >> (x - 1)) & 1) == 1)
            val = 0.0;
          else
            val = -1.0;


          val += (gfloat) ((double) (sample[ch][gr][sb] & ((1 << (x - 1)) - 1))
              / (double) (1L << (x - 1)));


          val += d_quant;
          val *= c_quant;


          val *= scale_val;
          fraction[ch][gr][sb] = val;
        }
      } else {
        fraction[ch][0][sb] = 0.0;
        fraction[ch][1][sb] = 0.0;
        fraction[ch][2][sb] = 0.0;
      }
    }
  }

  for (sb = sblimit; sb < SBLIMIT; sb++)
    for (ch = 0; ch < stereo; ch++) {
      fraction[ch][0][sb] = 0.0;
      fraction[ch][1][sb] = 0.0;
      fraction[ch][2][sb] = 0.0;
    }
}
