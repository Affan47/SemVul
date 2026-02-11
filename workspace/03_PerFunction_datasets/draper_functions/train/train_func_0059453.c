eet_eina_file_data_descriptor_class_set(Eet_Data_Descriptor_Class *eddc,

                                        unsigned int               eddc_size,
                                        const char                *name,
                                        int                        size)
{
   if (!eet_eina_stream_data_descriptor_class_set(eddc, eddc_size, name, size))
     return EINA_FALSE;

   eddc->version = EET_DATA_DESCRIPTOR_CLASS_VERSION;

   eddc->func.hash_add = (void *(*)(void *, const char *, void *))_eet_eina_hash_direct_add_alloc;
   eddc->func.str_direct_alloc = _eet_str_direct_alloc;
   eddc->func.str_direct_free = _eet_str_direct_free;

   return EINA_TRUE;
}
