mpz_mat_from_string(mpz_mat_t mat, const char *s)
{

   const char* whitespace = " \t\n\r";


   unsigned long r;
   if (!sscanf(s, "%ld", &r))
      return 0;


   s += strcspn(s, whitespace);


   s += strspn(s, whitespace);


   unsigned long c;
   if (!sscanf(s, "%ld", &c))
      return 0;


   s += strcspn(s, whitespace);


   s += strspn(s, whitespace);


   mpz_mat_clear(mat);
   mpz_mat_init(mat,r,c);

   for (unsigned long i = 0; i < r*c; i++)
   {


      s += strspn(s, whitespace);

      if (!gmp_sscanf(s, "%Zd", mat->entries[i]))
         return 0;


      s += strcspn(s, whitespace);

   }

   return 1;
}
