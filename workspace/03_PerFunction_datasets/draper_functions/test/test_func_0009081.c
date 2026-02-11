eina_convert_atod(const char *src, int length, long long *m, long *e)
{
   const char *str = src;
   long long mantisse;
   long exponent;
   int nbr_decimals = 0;
   int sign = 1;

   EINA_SAFETY_ON_NULL_RETURN_VAL(src, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(m,   EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(e,   EINA_FALSE);

   if (length <= 0)
      goto on_length_error;


   if (*str == '-')
     {
        sign = -1;
        str++;
        length--;
     }

   if (length <= 2)
      goto on_length_error;

   if (strncmp(str, "0x", 2))
     {
        eina_error_set(EINA_ERROR_CONVERT_0X_NOT_FOUND);
        DBG("'0x' not found in '%s'", src);
        return EINA_FALSE;
     }

   str += 2;
   length -= 2;

   mantisse = HEXA_TO_INT(*str);

   str++;
   length--; if (length <= 0)
      goto on_length_error;

   if (*str == '.')
      for (str++, length--;
           length > 0 && *str != 'p';
           ++str, --length, ++nbr_decimals)
        {
           mantisse <<= 4;
           mantisse += HEXA_TO_INT(*str);
        }

   if (sign < 0)
      mantisse = -mantisse;


   if (*str != 'p')
     {
        eina_error_set(EINA_ERROR_CONVERT_P_NOT_FOUND);
        DBG("'p' not found in '%s'", src);
        return EINA_FALSE;
     }

   sign = +1;

   str++;
   length--; if (length <= 0)
      goto on_length_error;

   if (strchr("-+", *str))
     {
        sign = (*str == '-') ? -1 : +1;

        str++; length--;
     }

   for (exponent = 0; length > 0 && *str != '\0'; ++str, --length)
     {
        exponent *= 10;
        exponent += *str - '0';
     }

   if (length < 0)
      goto on_length_error;

   if (sign < 0)
      exponent = -exponent;

   *m = mantisse;
   *e = exponent - (nbr_decimals << 2);

   return EINA_TRUE;

on_length_error:
   eina_error_set(EINA_ERROR_CONVERT_OUTRUN_STRING_LENGTH);
   return EINA_FALSE;
}
