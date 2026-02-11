evas_common_cpu_can_do(int *mmx, int *sse, int *sse2)
{
   static int do_mmx = 0, do_sse = 0, do_sse2 = 0, done = 0;

   if (!done)
     {
# ifdef HARD_CODED_P3
	cpu_feature_mask |= CPU_FEATURE_MMX;
	cpu_feature_mask |= CPU_FEATURE_SSE;
#endif
#ifdef HARD_CODED_P2
	cpu_feature_mask |= CPU_FEATURE_MMX;
#endif
	if (cpu_feature_mask & CPU_FEATURE_MMX) do_mmx = 1;
	if (cpu_feature_mask & CPU_FEATURE_MMX2) do_sse = 1;
	if (cpu_feature_mask & CPU_FEATURE_SSE) do_sse = 1;
     }

   *mmx = do_mmx;
   *sse = do_sse;
   *sse2 = do_sse2;
   done = 1;
}
