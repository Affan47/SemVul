speex_encode_stereo(float *data, int frame_size, SpeexBits *bits)
{
   int i, tmp;
   float e_left=0, e_right=0, e_tot=0;
   float balance, e_ratio;
   for (i=0;i<frame_size;i++)
   {
      e_left  += ((float)data[2*i])*data[2*i];
      e_right += ((float)data[2*i+1])*data[2*i+1];
      data[i] =  .5*(((float)data[2*i])+data[2*i+1]);
      e_tot   += ((float)data[i])*data[i];
   }
   balance=(e_left+1)/(e_right+1);
   e_ratio = e_tot/(1+e_left+e_right);


   speex_bits_pack(bits, 14, 5);
   speex_bits_pack(bits, SPEEX_INBAND_STEREO, 4);

   balance=4*log(balance);


   if (balance>0)
      speex_bits_pack(bits, 0, 1);
   else
      speex_bits_pack(bits, 1, 1);
   balance=floor(.5+fabs(balance));
   if (balance>30)
      balance=31;

   speex_bits_pack(bits, (int)balance, 5);


   tmp=scal_quant(e_ratio*Q15_ONE, e_ratio_quant_bounds, 4);
   speex_bits_pack(bits, tmp, 2);
}
