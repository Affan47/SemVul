putdelay(char* name, float delay)
{
   signal_list* signal;

   if (!name) {
      fprintf(stderr,"putdelay: no name\n");
      exit(1);
   }

   signal=getsignal(name,1);
   signal->DELAY_SET=1;
   signal->T=delay;
   if (signal->T<0) signal->T=0;
}
