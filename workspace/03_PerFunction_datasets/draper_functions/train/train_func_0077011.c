eet_data_node_read_cipher(Eet_File   *ef,
                          const char *name,
                          const char *cipher_key)
{
   const Eet_Dictionary *ed = NULL;
   const void *data = NULL;
   Eet_Node *result;
   Eet_Free_Context context;
   int required_free = 0;
   int size;

   ed = eet_dictionary_get(ef);

   if (!cipher_key)
     data = eet_read_direct(ef, name, &size);

   if (!data)
     {
        required_free = 1;
        data = eet_read_cipher(ef, name, &size, cipher_key);
        if (!data)
          return NULL;
     }

   eet_free_context_init(&context);
   result = _eet_data_descriptor_decode(&context, ed, NULL, data, size, NULL, 0);
   eet_free_context_shutdown(&context);

   if (required_free)
     free((void *)data);

   return result;
}
