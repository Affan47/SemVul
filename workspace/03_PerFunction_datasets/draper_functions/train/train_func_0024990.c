cutcmp(const void *cut0ptr, const void *cut1ptr)
{
   cut_data *cut0 = *((cut_data **)cut0ptr);
   cut_data *cut1 = *((cut_data **)cut1ptr);
   int typediff, sizediff;

   if ((typediff = cut0->type - cut1->type))  return(typediff);
   if ((sizediff = cut0->size - cut1->size))  return(sizediff);
   return( MEMCMP(cut0->coef, cut1->coef, cut0->size) );
}
