sync_process_install_file(int sd)
{
   FILE *in;
   FILE *out;
   char line[1002];
   char *Pc;
   int r, line_count;
   char vfsdir[] = "/PALM/Launcher/";

   in = jp_open_home_file(EPN".install", "r");
   if (!in) {
      jp_logf(JP_LOG_WARN, _("Unable to open file: %s%s\n"), EPN, ".install");
      return EXIT_FAILURE;
   }

   out = jp_open_home_file(EPN".install.tmp", "w");
   if (!out) {
      jp_logf(JP_LOG_WARN, _("Unable to open file: %s%s\n"), EPN, ".install.tmp");
      fclose(in);
      return EXIT_FAILURE;
   }

   for (line_count=0; (!feof(in)); line_count++) {
      line[0]='\0';
      Pc = fgets(line, 1000, in);
      if (!Pc) {
         break;
      }
      if (line[strlen(line)-1]=='\n') {
         line[strlen(line)-1]='\0';
      }
      if (line[0] == '\001') {

         r = sync_install(&(line[1]), sd, vfsdir);
      } else {
         r = sync_install(line, sd, NULL);
      }

      if (r==0) {
         continue;
      }
      fprintf(out, "%s\n", line);
   }
   fclose(in);
   fclose(out);

   rename_file(EPN".install.tmp", EPN".install");

   return EXIT_SUCCESS;
}
