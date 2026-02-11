rend_freeze(unsigned long interval)
{
   int reason;
   while(1)
   {
      if ((reason = disp_freeze(interval)) == RESIZE)
         rend_setsize();
      else
         return(reason);
   }

}
