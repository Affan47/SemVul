flam3_atoi(char *nstr) {


   int res;
   char *endp;


   errno=0;


   res = strtol(nstr, &endp, 10);


   if (endp!=nstr+strlen(nstr)) {
      flam3_conversion_failed = 1;
      fprintf(stderr,"flam3_atoi : Error converting :%s: extra chars\n",nstr);
   }
   if (errno) {
      flam3_conversion_failed = 1;
      fprintf(stderr,"flam3_atoi : Error converting :%s:\n",nstr);
   }
   return(res);
}
