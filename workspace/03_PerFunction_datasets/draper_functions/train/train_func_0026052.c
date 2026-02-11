spool_flatfile_open_file(lList **answer_list,
                         const spool_flatfile_destination destination,
                         const char *filepath_in,
                         const char **filepath_out)
{
#ifdef USE_FOPEN
   FILE *fd = NULL;
#else
   int fd = -1;
#endif

   DENTER(FLATFILE_LAYER, "spool_flatfile_open_file");

   *filepath_out = NULL;

   switch (destination) {
      case SP_DEST_SPOOL:

         if (filepath_in == NULL || filepath_in[0] == '\0') {
            answer_list_add_sprintf(answer_list, STATUS_ESEMANTIC,
                                    ANSWER_QUALITY_ERROR,
                                    MSG_INVALIDFILENAMENULLOREMPTY);
            DRETURN(fd);
         }


#ifdef USE_FOPEN
         fd = fopen(filepath_in, "w");
         if (fd == NULL) {
#else
         fd = open(filepath_in, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
         if (fd == -1) {
#endif
            answer_list_add_sprintf(answer_list, STATUS_EDISK,
                                    ANSWER_QUALITY_ERROR,
                                    MSG_ERROROPENINGFILEFORWRITING_SS,
                                    filepath_in, strerror(errno));
         }

         *filepath_out = strdup(filepath_in);
         break;
      case SP_DEST_TMP:
         {
            char buffer[SGE_PATH_MAX];
            dstring tmp_name_error = DSTRING_INIT;


            filepath_in = sge_tmpnam(buffer, &tmp_name_error);
            if (filepath_in == NULL) {
               if (sge_dstring_get_string(&tmp_name_error) != NULL) {
                  answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                       ANSWER_QUALITY_ERROR,
                                       sge_dstring_get_string(&tmp_name_error));
               } else {
                  answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                       ANSWER_QUALITY_ERROR,
                                       MSG_ERRORGETTINGTMPNAM_S,
                                       strerror(errno));
               }
               sge_dstring_free(&tmp_name_error);
               DRETURN(fd);
            }
            sge_dstring_free(&tmp_name_error);


#ifdef USE_FOPEN
            fd = fopen(filepath_in, "w");
            if (fd == NULL) {
#else
            fd = open(filepath_in, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
            if (fd == -1) {
#endif
               answer_list_add_sprintf(answer_list, STATUS_EDISK,
                                       ANSWER_QUALITY_ERROR,
                                       MSG_ERROROPENINGFILEFORWRITING_SS,
                                       filepath_in, strerror(errno));
               DRETURN(fd);
            }
            *filepath_out = strdup(filepath_in);
         }
         break;
      case SP_DEST_STDOUT:
#ifndef USE_FOPEN
         fd = 1;
#endif

#if !defined(DARWIN6)
         flockfile(stdout);
#endif
         fflush(stdout);
         *filepath_out = strdup("<stdout>");
         break;
      case SP_DEST_STDERR:
#ifndef USE_FOPEN
         fd = 2;
#endif

#if !defined(DARWIN6)
         flockfile(stderr);
#endif
         fflush(stderr);
         *filepath_out = strdup("<stderr>");
         break;
   }

   DRETURN(fd);
}
