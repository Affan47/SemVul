cat_compare(const void *v1, const void *v2)
{
   struct sorted_cats *s1, *s2;
   s1=(struct sorted_cats *)v1; s2=(struct sorted_cats *)v2;
   if ((s1)->Pcat[0]=='\0') {
      return 1;
   }
   if ((s2)->Pcat[0]=='\0') {
      return -1;
   }
   return strcmp((s1)->Pcat, (s2)->Pcat);
}
