gozer_stream_file(char *file, int headers)
{
   FILE *fp;
   int c;

   if (headers)
   {

      char *extension;

      extension = strrchr(file, '.');
      extension++;
      if (extension)
      {
         if (!strcasecmp(extension, "jpg"))
            printf("Content-type: image/jpeg\n");
         else
            printf("Content-type: image/%s\n", extension);
      }
      else
         weprintf("couldn't determine file extension for mime type setting");
      printf("\n");
   }

   fp = fopen(file, "r");
   if (!fp)
   {
      weprintf("couldn't open file %s for streaming\n", file);
      return;
   }
   while (!feof(fp))
   {
      c = fgetc(fp);
      fputc(c, stdout);
   }
}
