apu_triangle(triangle_t *chan)
{
   int freq;
   int8 output;


   if (FALSE == chan->enabled)
      return 0;

   if (FALSE == chan->counter_started && 0 == (chan->regs[0] & 0x80))
   {
      if (chan->write_latency)
         chan->write_latency--;
      if (0 == chan->write_latency)
         chan->counter_started = TRUE;
   }

   if (chan->counter_started)
   {
      if (chan->linear_length > 0)
         chan->linear_length--;
      if (chan->vbl_length && 0 == (chan->regs[0] & 0x80))
            chan->vbl_length--;

      if (0 == chan->vbl_length)
         return 0;
   }

   if (0 == chan->linear_length)
      return 0;

   freq = (((chan->regs[3] & 7) << 8) + chan->regs[2]) + 1;

   if (freq < 4)
      return 0;

   chan->phaseacc -= (float) apu_incsize;
   while (chan->phaseacc < 0)
   {
      chan->phaseacc += freq;
      chan->adder = (chan->adder + 1) & 0x1F;

      output = (chan->adder & 7) << 1;
      if (chan->adder & 8)
         output = 0x10 - output;
      if (chan->adder & 0x10)
         output = -output;

      chan->output_vol = output;
   }

   return (int8) chan->output_vol;
}
