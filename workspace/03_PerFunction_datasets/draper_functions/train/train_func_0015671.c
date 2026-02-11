cpu()
{
  if(arg_verbose)
    Debug( "%.2f CPU seconds used; %lu seconds elapsed (%.2f%% usage)",
      clock() / (double)CLOCKS_PER_SEC,
      (unsigned long)(time((time_t *)0) - BTCONTENT.GetStartTime()),
      clock() / (double)CLOCKS_PER_SEC /
        (time((time_t *)0) - BTCONTENT.GetStartTime()) * 100 );
}
