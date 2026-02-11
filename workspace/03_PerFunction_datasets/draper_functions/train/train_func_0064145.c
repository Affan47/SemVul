compute_gain_floor(int noise_suppress, int effective_echo_suppress, spx_word32_t *noise, spx_word32_t *echo, spx_word16_t *gain_floor, int len)
{
   int i;
   float echo_floor;
   float noise_floor;

   noise_floor = exp(.2302585f*noise_suppress);
   echo_floor = exp(.2302585f*effective_echo_suppress);


   for (i=0;i<len;i++)
      gain_floor[i] = FRAC_SCALING*sqrt(noise_floor*PSHR32(noise[i],NOISE_SHIFT) + echo_floor*echo[i])/sqrt(1+PSHR32(noise[i],NOISE_SHIFT) + echo[i]);
}
