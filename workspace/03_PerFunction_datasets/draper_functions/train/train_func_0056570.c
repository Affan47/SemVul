nc4_att_list_add(NC_ATT_INFO_T **list)
{
   NC_ATT_INFO_T *att, *a1;
   if (!(att = calloc(1, sizeof(NC_ATT_INFO_T))))
      return NC_ENOMEM;
   if (*list)
   {
      for (a1 = *list; a1; a1 = a1->next)
         if (!a1->next)
            break;
      a1->next = att;
      att->prev = a1;
   }
   else
   {
      *list = att;
   }

   return NC_NOERR;
}
