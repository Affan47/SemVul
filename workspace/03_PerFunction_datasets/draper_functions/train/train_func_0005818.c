var2n(const char *s) {
   int i;

   for (i = 0; i < flam3_nvariations; i++)
      if (!strcmp(s, flam3_variation_names[i])) return i;

   return flam3_variation_none;
}
