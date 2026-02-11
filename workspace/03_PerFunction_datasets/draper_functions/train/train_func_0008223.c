_eina_value_type_string_pset(const Eina_Value_Type *type __UNUSED__, void *mem, const void *ptr)
{
   char **tmem = mem;
   const char * const *str = ptr;
   eina_error_set(0);
   if (*str == *tmem) return EINA_TRUE;
   if (!*str)
     {
        free(*tmem);
        *tmem = NULL;
     }
   else
     {
        char *tmp = strdup(*str);
        if (!tmp)
          {
             eina_error_set(EINA_ERROR_OUT_OF_MEMORY);
             return EINA_FALSE;
          }
        free(*tmem);
        *tmem = tmp;
     }
   return EINA_TRUE;
}
