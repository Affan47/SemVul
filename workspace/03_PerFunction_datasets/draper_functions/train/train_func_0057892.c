path_alias_list_initialize(lList **path_alias_list,
                               lList **alpp,
                               const char *cell_root,
                               const char *user,
                               const char *host)
{
   char filename[2][SGE_PATH_MAX];
   char err[BUFSIZ];
   DENTER(TOP_LAYER, "path_alias_list_initialize");


   {
      struct passwd *pwd;
      struct passwd pw_struct;
      char *buffer;
      int size;

      size = get_pw_buffer_size();
      buffer = sge_malloc(size);
      pwd = sge_getpwnam_r(user, &pw_struct, buffer, size);

      if (!pwd) {
         sprintf(err, MSG_USER_INVALIDNAMEX_S, user);
         answer_list_add(alpp, err, STATUS_ENOSUCHUSER, ANSWER_QUALITY_ERROR);
         FREE(buffer);
         DRETURN(-1);
      }
      if (!pwd->pw_dir) {
         sprintf(err, MSG_USER_NOHOMEDIRFORUSERX_S, user);
         answer_list_add(alpp, err, STATUS_EDISK, ANSWER_QUALITY_ERROR);
         FREE(buffer);
         DRETURN(-1);
      }
      sprintf(filename[0], "%s/%s", cell_root, PATH_ALIAS_COMMON_FILE);
      sprintf(filename[1], "%s/%s", pwd->pw_dir, PATH_ALIAS_HOME_FILE);

      FREE(buffer);
   }


   {
      int i;

      for (i=0; i<2; i++) {
         if (path_alias_read_from_file(path_alias_list,
                                       alpp, filename[i]) != 0) {
            sprintf(err, MSG_ALIAS_CANTREAD_SS, filename[i], strerror(errno));
            answer_list_add(alpp, err, STATUS_EDISK, ANSWER_QUALITY_ERROR);
            DEXIT;
            return -1;
         }
      }
   }


   {
      lCondition *where = NULL;

      where = lWhere("%T(%I == %s || %I == %s)", PA_Type,
                     PA_submit_host, "*", PA_submit_host, host);
      *path_alias_list = lSelectDestroy(*path_alias_list, where);
      lFreeWhere(&where);
   }

   DEXIT;
   return 0;
}
