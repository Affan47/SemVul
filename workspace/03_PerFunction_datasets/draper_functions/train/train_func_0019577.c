compute_opt_delay(JitterBuffer *jitter)
{
   int i;
   spx_int16_t opt=0;
   spx_int32_t best_cost=0x7fffffff;
   int late = 0;
   int pos[MAX_BUFFERS];
   int tot_count;
   float late_factor;
   int penalty_taken = 0;
   int best = 0;
   int worst = 0;
   spx_int32_t deltaT;
   struct TimingBuffer *tb;

   tb = jitter->_tb;


   tot_count = 0;
   for (i=0;i<MAX_BUFFERS;i++)
      tot_count += tb[i].curr_count;
   if (tot_count==0)
      return 0;


   if (jitter->latency_tradeoff != 0)
      late_factor = jitter->latency_tradeoff * 100.0f / tot_count;
   else
      late_factor = jitter->auto_tradeoff * jitter->window_size/tot_count;


   for (i=0;i<MAX_BUFFERS;i++)
      pos[i] = 0;


   for (i=0;i<TOP_DELAY;i++)
   {
      int j;
      int next=-1;
      int latest = 32767;

      for (j=0;j<MAX_BUFFERS;j++)
      {
         if (pos[j] < tb[j].filled && tb[j].timing[pos[j]] < latest)
         {
            next = j;
            latest = tb[j].timing[pos[j]];
         }
      }
      if (next != -1)
      {
         spx_int32_t cost;

         if (i==0)
            worst = latest;
         best = latest;
         latest = ROUND_DOWN(latest, jitter->delay_step);
         pos[next]++;


         cost = -latest + late_factor*late;

         if (cost < best_cost)
         {
            best_cost = cost;
            opt = latest;
         }
      } else {
         break;
      }


      late++;

      if (latest >= 0 && !penalty_taken)
      {
         penalty_taken = 1;
         late+=4;
      }
   }

   deltaT = best-worst;

   jitter->auto_tradeoff = 1 + deltaT/TOP_DELAY;


   if (tot_count < TOP_DELAY && opt > 0)
      return 0;
   return opt;
}
