drmaa_expand_wd_path(const char*username, const char *path, lList **answer_list)
{
   char *file = NULL;
   char str[256 + 1];

   DENTER(TOP_LAYER, "drmaa_expand_wd_path");
   DPRINTF(("Expanding \"%s\"\n", path));


   if (strstr(path, "$TASK_ID") != NULL) {
         sprintf(str, MSG_DRMAA_INC_NOT_ALLOWED);
         answer_list_add(answer_list, str, STATUS_ENOSUCHUSER,
                         ANSWER_QUALITY_ERROR);
         DRETURN(NULL);
   }


   if (!strncmp(path, "$HOME", 5)) {
      int length = 0;
      char *homedir = drmaa_get_home_directory(username, answer_list);

      if (homedir == NULL) {
         DRETURN(NULL);
      }

      length = strlen(path) - 5 + strlen(homedir) + 1;

      file = (char *)malloc(sizeof(char) * length);
      strcpy(file, homedir);
      file = strcat(file, path + 5);

      FREE(homedir);
   }
   else {
      file = (char *)malloc(sizeof(char) * (strlen(path) + 1));
      file = strcpy(file, path);
   }

   DPRINTF(("Expanded to \"%s\"\n", file));
   DRETURN(file);
}
