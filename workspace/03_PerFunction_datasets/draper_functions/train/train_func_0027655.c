critical_delay(lofig_list* lofig)
{
   losig_list* losig;
   char* signame;

   losig=critical_output(lofig);

   if (!losig->NAMECHAIN) {
      fprintf(stderr,"critical_delay: no losig name\n");
      autexit(1);
   }
   signame=losig->NAMECHAIN->DATA;

   if (losig->TYPE==EXTERNAL) return getdelay(output_name(signame));
   return getdelay(signame);
}
