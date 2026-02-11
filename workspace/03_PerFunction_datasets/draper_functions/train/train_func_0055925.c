brhood_calc(int radius, char method)
{
   void * brhood_wthread(void *arg);

   int      rad, rad2, dx, dy, cc, ii;
   double   kern;

   brhood_radius = radius;
   brhood_method = method;

   if (brhood_method == 'g')
   {
      rad = brhood_radius;
      rad2 = rad * rad;

      for (dy = -rad; dy <= rad; dy++)
      for (dx = -rad; dx <= rad; dx++)
      {
         if (dx*dx + dy*dy <= rad2)
            kern = exp( - (dx*dx + dy*dy) / rad2);
         else kern = 0;
         brhood_kernel[dy+rad][dx+rad] = kern;
      }
   }

   if (brhood_brightness) zfree(brhood_brightness);
   cc = E1ww * E1hh * sizeof(float);
   brhood_brightness = (float *) zmalloc(cc,"brhood");
   memset(brhood_brightness,0,cc);

   if (Factivearea) SB_goal = sa_Npixel;
   else SB_goal = E1ww * E1hh;
   SB_done = 0;

   for (ii = 0; ii < Nwt; ii++)
      start_wthread(brhood_wthread,&wtnx[ii]);
   wait_wthreads();

   SB_goal = 0;
   return;
}
