clock_resample_interpolate(cycle_count& delta_t, short* buf, int n,
            int interleave)
{
  int s = 0;

  for (;;) {
    cycle_count next_sample_offset = sample_offset + cycles_per_sample;
    cycle_count delta_t_sample = next_sample_offset >> FIXP_SHIFT;
    if (delta_t_sample > delta_t) {
      break;
    }
    if (s >= n) {
      return s;
    }
    for (int i = 0; i < delta_t_sample; i++) {
      clock();
      sample[sample_index] = sample[sample_index + RINGSIZE] = output();
      ++sample_index;
      sample_index &= 0x3fff;
    }
    delta_t -= delta_t_sample;
    sample_offset = next_sample_offset & FIXP_MASK;

    int fir_offset = sample_offset*fir_RES >> FIXP_SHIFT;
    int fir_offset_rmd = sample_offset*fir_RES & FIXP_MASK;
    short* fir_start = fir + fir_offset*fir_N;
    short* sample_start = sample + sample_index - fir_N + RINGSIZE;


    int v1 = 0;
    for (int j = 0; j < fir_N; j++) {
      v1 += sample_start[j]*fir_start[j];
    }


    if (++fir_offset == fir_RES) {
      fir_offset = 0;
      --sample_start;
    }
    fir_start = fir + fir_offset*fir_N;


    int v2 = 0;
    for (int j = 0; j < fir_N; j++) {
      v2 += sample_start[j]*fir_start[j];
    }


    int v = v1 + (fir_offset_rmd*(v2 - v1) >> FIXP_SHIFT);

    v >>= FIR_SHIFT;


    const int half = 1 << 15;
    if (v >= half) {
      v = half - 1;
    }
    else if (v < -half) {
      v = -half;
    }

    buf[s++*interleave] = v;
  }

  for (int i = 0; i < delta_t; i++) {
    clock();
    sample[sample_index] = sample[sample_index + RINGSIZE] = output();
    ++sample_index;
    sample_index &= 0x3fff;
  }
  sample_offset -= delta_t << FIXP_SHIFT;
  delta_t = 0;
  return s;
}
