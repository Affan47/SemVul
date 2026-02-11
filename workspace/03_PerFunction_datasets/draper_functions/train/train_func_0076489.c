saveprefs (char * directory, char * filename)
{
   char fullpath[TEXTBUFFERSIZE];

   FILE * outfile;

   if (strlen(directory) + strlen(filename) >= sizeof(fullpath))
   {
      fprintf(stderr, "Error while saving %s:\n", filename);
      fprintf(stderr, "Size of directory name (%u chars) plus size of file name (%u chars)\n",
			(unsigned int) strlen(directory), (unsigned int) strlen(filename));
      fprintf(stderr, "is too long (over %u chars), and would cause a buffer overflow...\n",
			(unsigned int) (sizeof(fullpath) - 1));
      return;
   }
   strcpy(fullpath, directory);
   strcat(fullpath, filename);

   if ((outfile = fopen(fullpath, "wb")) == NULL)
   {
      fprintf(stderr, "Failed to open prefs file %s for save.\n", fullpath);
      return;
   } else {
      putc(PREFSVERSION, outfile);
      putc(delay, outfile);
      putc(highscore & 0x000000FF, outfile);
      putc((highscore & 0x0000FF00) >> 8, outfile);
      putc((highscore & 0x00FF0000) >> 16, outfile);
      putc((highscore & 0xFF000000) >> 24, outfile);
      putc(shuffle, outfile);
      fclose(outfile);
   }

   return;
}
