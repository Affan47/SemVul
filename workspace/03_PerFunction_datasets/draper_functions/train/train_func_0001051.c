_ZmodF_mul_fft_reduce_modB(unsigned long* out, ZmodF_t* in,
                                unsigned long len)
{
   for (unsigned long i = 0; i < len; i++)
      out[i] = in[i][0];
}
