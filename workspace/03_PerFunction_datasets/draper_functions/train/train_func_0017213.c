special_strcmpi(const char *s1, const char *s2, size_t n)
   {
      int lc1  = 0;
      int lc2  = 0;

      while (n--)
      {
         lc1 = tolower(*s1);
         lc2 = tolower(*s2);

         if (lc1 != lc2)
            return (lc1 - lc2);

         if (!lc1)
            return 0;

         ++s1;
         ++s2;
      }

      return 0;
   }
