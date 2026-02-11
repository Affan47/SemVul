eet_data_chunk_get(const Eet_Dictionary *ed,
                   Eet_Data_Chunk       *chnk,
                   const void           *src,
                   int                   size)
{
   const char *s;
   int ret1, ret2;

   if (!src)
     return;

   if (size <= 8)
     return;

   if (!chnk)
     return;

   s = src;
   if (s[2] == 'K')
     {
        if ((s[0] != 'C') || (s[1] != 'H') || (s[2] != 'K'))
          return;

        chnk->type = (unsigned char)(s[3]);
        if (chnk->type >= EET_I_LIMIT)
          {
             chnk->group_type =
               ((chnk->type - EET_I_LIMIT) & 0xF) + EET_G_UNKNOWN;
             switch ((chnk->type - EET_I_LIMIT) & 0xF0)
               {
#define EET_UNMATCH_TYPE(Type) \
case EET_I_ ## Type: chnk->type = EET_T_ ## Type; break;

                  EET_UNMATCH_TYPE(STRING);
                  EET_UNMATCH_TYPE(INLINED_STRING);
                  EET_UNMATCH_TYPE(NULL);

                default:
                  return;
               }
          }
        else if (chnk->type > EET_T_LAST)
          {
             chnk->group_type = chnk->type;
             chnk->type = EET_T_UNKNOW;
          }
        else
          chnk->group_type = EET_G_UNKNOWN;
        if ((chnk->type >= EET_T_LAST) ||
            (chnk->group_type >=
             EET_G_LAST))
          {
             chnk->type = 0;
             chnk->group_type = 0;
          }
     }
   else if ((s[0] != 'C') || (s[1] != 'H') || (s[2] != 'n') || (s[3] != 'K'))
     return;

   ret1 = eet_data_get_type(ed, EET_T_INT, (s + 4), (s + size), &(chnk->size));

   if (ret1 <= 0)
     return;

   if ((chnk->size < 0) || ((chnk->size + 8) > size))
     return;

   ret2 = eet_data_get_type(ed, EET_T_STRING, (s + 8), (s + size), &(chnk->name));

   if (ret2 <= 0)
     return;

   chnk->len = ret2;


   chnk->hash = eet_data_get_string_hash(ed, (s + 8), (s + size));

   if (ed)
     {
        chnk->data = (char *)src + 4 + ret1 + sizeof(int);
        chnk->size -= sizeof(int);
     }
   else
     {
        chnk->data = (char *)src + 4 + ret1 + chnk->len;
        chnk->size -= chnk->len;
     }

   return;
}
