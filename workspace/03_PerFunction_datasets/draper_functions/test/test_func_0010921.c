_fash_int_add(Fash_Int *fash, int item, RGBA_Font_Int *fint, int idx)
{
   int grp, maj, min;


   grp = (item >> 16) & 0xff;
   maj = (item >> 8) & 0xff;
   min = item & 0xff;
   if (!fash->bucket[grp])
     fash->bucket[grp] = calloc(1, sizeof(Fash_Int_Map2));
   EINA_SAFETY_ON_NULL_RETURN(fash->bucket[grp]);
   if (!fash->bucket[grp]->bucket[maj])
     fash->bucket[grp]->bucket[maj] = calloc(1, sizeof(Fash_Int_Map));
   EINA_SAFETY_ON_NULL_RETURN(fash->bucket[grp]->bucket[maj]);
   fash->bucket[grp]->bucket[maj]->item[min].fint = fint;
   fash->bucket[grp]->bucket[maj]->item[min].index = idx;
}
