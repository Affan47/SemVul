imf_context_data_new()
{
   Ecore_IMF_Context_Data *imf_context_data = NULL;
   char *locale;

   locale = setlocale(LC_CTYPE, "");
   if (!locale) return NULL;

   if (!XSupportsLocale()) return NULL;

   imf_context_data = calloc(1, sizeof(Ecore_IMF_Context_Data));
   EINA_SAFETY_ON_NULL_RETURN_VAL(imf_context_data, NULL);

   imf_context_data->locale = strdup(locale);
   if (!imf_context_data->locale) goto error;

   return imf_context_data;
error:
   imf_context_data_destroy(imf_context_data);
   return NULL;
}
