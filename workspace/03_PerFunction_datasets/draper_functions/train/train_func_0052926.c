argv2str(int argc, char *argv[])
{
   char *result;
   int   len;
   int   off;
   int   i;


   len = 0;
   for (i = 0; i < argc; i++) {
      len += strlen(argv[i]) + 1;
      if (strstr(argv[i], " ") != NULL)
         len += 2;
   }


   if ((result = calloc(len, sizeof(char))) == NULL)
      err(1, "argv2str: calloc failed");
   bzero(result, len);


   off = 0;
   for (i = 0; i < argc; i++) {
      if (strstr(argv[i], " ") == NULL)
         off += snprintf(result + off, len, "%s ", argv[i]);
      else
         off += snprintf(result + off, len, "\'%s\' ", argv[i]);
   }

   return result;
}
