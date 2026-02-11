str_hash(void *str)
{
   char *p,*s = (char *)str;
   u_int h,g;

   for(h=0,p=s;*p!='\0';p+=1)
   {
      h = (h << 4) + *p;
      if ((g = h & 0xf0000000)) {
         h = h ^ (g >> 24);
         h = h ^ g;
      }
   }

   return(h);
}
