zmod_poly_from_string(zmod_poly_t poly, char* s)
{
   const char* whitespace = " \t\n\r";

   unsigned long p, length;
   if (!sscanf(s, "%ld %ld  ", &length, &p))
      return 0;


   s += strcspn(s, whitespace);
   s += strspn(s, whitespace);
   s += strcspn(s, whitespace);
   s += strspn(s, whitespace);

	poly->length = 0;
   zmod_poly_fit_length(poly, length);

   for (unsigned long i = 0; i < length; i++)
   {

      s += strspn(s, whitespace);

      if (!sscanf(s, "%ld", &poly->coeffs[i]))
         return 0;
      poly->length++;


      s += strcspn(s, whitespace);
   }

   __zmod_poly_normalise(poly);

   return 1;
}
