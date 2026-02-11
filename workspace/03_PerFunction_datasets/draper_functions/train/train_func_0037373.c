eet_data_put_variant(Eet_Dictionary      *ed,
                     Eet_Data_Descriptor *edd __UNUSED__,
                     Eet_Data_Element    *ede,
                     Eet_Data_Stream     *ds,
                     void                *data_in)
{
   const char *union_type;
   void *data;
   Eina_Bool unknow = EINA_FALSE;
   int size;
   int i;

   EET_ASSERT(!((ede->type != EET_T_UNKNOW) || (!ede->subtype)), return );

   union_type = ede->subtype->func.type_get(
       ((char *)data_in) + ede->count - ede->offset,
       &unknow);

   if (!union_type && unknow == EINA_FALSE)
     return;

   if (unknow)
     {

         Eet_Variant_Unknow *evu;

         data = eet_data_put_type(ed, EET_T_STRING, &union_type, &size);
         if (data)
           eet_data_encode(ed,
                           ds,
                           data,
                           ede->name,
                           size,
                           ede->type,
                           ede->group_type);

         evu = (Eet_Variant_Unknow *)data_in;
         if (evu && EINA_MAGIC_CHECK(evu, EET_MAGIC_VARIANT))
           eet_data_encode(ed,
                           ds,
                           evu->data,
                           ede->name,
                           evu->size,
                           ede->type,
                           ede->group_type);
     }
   else

     for (i = 0; i < ede->subtype->elements.num; ++i)
       if (strcmp(ede->subtype->elements.set[i].name, union_type) == 0)
         {
            Eet_Data_Element *sede;


            data = eet_data_put_type(ed, EET_T_STRING, &union_type, &size);
            if (data)
              eet_data_encode(ed,
                              ds,
                              data,
                              ede->name,
                              size,
                              ede->type,
                              ede->group_type);

            sede = &(ede->subtype->elements.set[i]);

            if (sede->group_type != EET_G_UNKNOWN)
              {
                 Eet_Data_Stream *lds;

                 lds = eet_data_stream_new();
                 eet_group_codec[sede->group_type - 100].put(ed,
                                                             sede->subtype,
                                                             sede,
                                                             lds,
                                                             data_in);
                 if (lds->size != 0)
                   {
                      eet_data_encode(ed, ds, lds->data, ede->name, lds->pos,
                                      ede->type, ede->group_type);

                      lds->data = NULL;
                      lds->size = 0;
                   }
                 else
                   eet_data_encode(ed, ds, NULL, ede->name, 0,
                                   EET_T_NULL, ede->group_type);

                 eet_data_stream_free(lds);
              }
            else
              {
                 data = _eet_data_descriptor_encode(ed,
                                                    sede->subtype,
                                                    *(void **)data_in,
                                                    &size);
                 if (data)
                   eet_data_encode(ed,
                                   ds,
                                   data,
                                   ede->name,
                                   size,
                                   ede->type,
                                   ede->group_type);
              }

            break;
         }
}
