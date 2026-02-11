GetTimeout()
{
   while(chain_running && chain_running->Stopped())
      chain_running->re_sort();
   if(!chain_running)
      return infty_count?HOUR*1000:-1;
   TimeDiff remains(chain_running->stop,now);
   return remains.MilliSeconds();
}
