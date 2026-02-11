getHomeDir(
char *exp_path,
const char *user
) {
   struct passwd *pwd;
   struct passwd pw_struct;
   char *buffer;
   int size;

   DENTER(TOP_LAYER, "getHomeDir");

   size = get_pw_buffer_size();
   buffer = sge_malloc(size);

   pwd = sge_getpwnam_r(user, &pw_struct, buffer, size);
   if (!pwd) {
      ERROR((SGE_EVENT, MSG_EXECD_INVALIDUSERNAME_S, user));
      FREE(buffer);
      DEXIT;
      return 0;
   }
   if (!pwd->pw_dir) {
      ERROR((SGE_EVENT, MSG_EXECD_NOHOMEDIR_S, user));
      FREE(buffer);
      DEXIT;
      return 0;

   }
   strcat(exp_path, pwd->pw_dir);

   FREE(buffer);
   DEXIT;
   return 1;
}
