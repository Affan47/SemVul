eio_eet_data_read_cipher(Eet_File *ef,
			 Eet_Data_Descriptor *edd,
			 const char *name,
			 const char *cipher_key,
			 Eio_Done_ERead_Cb done_cb,
			 Eio_Error_Cb error_cb,
			 const void *data)
{
   Eio_Eet_Read *er;

   EINA_SAFETY_ON_NULL_RETURN_VAL(ef, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(edd, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(name, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(done_cb, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(error_cb, NULL);

   er = malloc(sizeof (Eio_Eet_Read));
   EINA_SAFETY_ON_NULL_RETURN_VAL(er, NULL);

   er->ef = ef;
   er->edd = edd;
   er->name = eina_stringshare_add(name);
   er->cipher_key = eina_stringshare_add(cipher_key);
   er->done_cb.eread = done_cb;

   if (!eio_file_set(&er->common,
                     NULL,
                     error_cb,
                     data,
                     _eio_eet_data_read_cipher_job,
                     _eio_eet_data_read_cipher_end,
                     _eio_eet_data_read_cipher_cancel))
     return NULL;

   return &er->common;
}
