clean_month (char *s)
{
   if ((s == NULL) || (*s == '\0'))
      return NULL;

   char *buffer = xmalloc (strlen (s) + 1);
   if (sscanf (s, "%6[^|]", buffer) != 1) {
      free (buffer);
      return NULL;
   }

   return buffer;
}
