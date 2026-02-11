eet_data_get_list(Eet_Free_Context     *context,
                  const Eet_Dictionary *ed,
                  Eet_Data_Descriptor  *edd,
                  Eet_Data_Element     *ede,
                  Eet_Data_Chunk       *echnk,
                  int                   type,
                  int                   group_type __UNUSED__,
                  void                 *data,
                  char                **p,
                  int                  *size)
{
   Eet_Data_Descriptor *subtype = NULL;
   void *list = NULL;
   void **ptr;
   void *data_ret;

   EET_ASSERT(!((type > EET_T_UNKNOW) && (type < EET_T_STRING)), return 0);

   if (ede)
     {
        subtype = ede->subtype;

        if (type != ede->type)
          return 0;
     }

   ptr = (void **)data;
   list = *ptr;
   data_ret = NULL;

   if (IS_POINTER_TYPE(type))
     POINTER_TYPE_DECODE(context,
                         ed,
                         edd,
                         ede,
                         echnk,
                         type,
                         &data_ret,
                         p,
                         size,
                         on_error);
   else
     STRUCT_TYPE_DECODE(data_ret,
                        context,
                        ed,
                        subtype,
                        echnk->data,
                        echnk->size,
                        -1,
                        on_error);

   if (edd)
     {
        list = edd->func.list_append(list, data_ret);
        *ptr = list;
        _eet_freelist_list_add(context, ptr);
     }
   else
     eet_node_list_append(*((Eet_Node **)data), echnk->name, data_ret);

   return 1;

on_error:
   return 0;
}
