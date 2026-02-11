mkinitcap(char * p, const struct cs_info * csconv)
 {
   if (*p != '\0') *p = csconv[((unsigned char)*p)].cupper;
 }
