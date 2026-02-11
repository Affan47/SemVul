commControl(int channel, int spec, int value)
{

   if(channel==255)
   {

      return txControl(spec, value);
   }
   else if (channel==0)
   {

      return 0;
   }
   else if (channel==1)
   {

      return fftControl(spec, value);
   }
   else if (channel>=COMM_RXCH&&channel<N_BUFFERS)
   {

      return rxControl(channel, spec, value);
   }
   else
   {
      return -1;
   }
}
