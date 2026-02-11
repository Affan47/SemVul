get_output_template (const char *image_name, const char *wfa_name,
		     bool_t color, char **basename, char **suffix)


{
   if (!wfa_name || streq (wfa_name, "-"))
      wfa_name = "stdin";


   if (!image_name || streq (image_name, "") || streq (image_name, "-"))
   {
      *basename = strdup (wfa_name);
      *suffix   = NULL;
   }
   else
   {
      *basename = strdup (image_name);
      *suffix   = strrchr (*basename, '.');
   }

   if (*suffix)
   {
      **suffix = 0;
      (*suffix)++;
      if (**suffix == 0)
	 *suffix = strdup (color ? "ppm" : "pgm");
   }
   else
      *suffix = strdup (color ? "ppm" : "pgm");
}
