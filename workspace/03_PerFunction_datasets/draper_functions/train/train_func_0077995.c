readchars_file(char *fn, long offset, int *nread)
{
   FILE *fd = fopen(fn, "r");
   if (fd == NULL) {
       fprintf(stderr, "Unable to open file <%s>: ", fn);
       perror("");
       exit(1);
   }
   if(fseek(fd, offset, SEEK_SET) == EOF) fatal("seek failed");

   char *result = MALLOC(*nread);
   memset(result, 0, *nread);
   int nbytesread = fread(result, 1, *nread, fd);


   if(nbytesread != *nread)
      fatal("fread failed");

   fclose(fd);
   return result;
}
