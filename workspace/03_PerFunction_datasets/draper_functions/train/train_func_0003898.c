sge_edit(const char *fname, uid_t myuid, gid_t mygid)
{
   SGE_STRUCT_STAT before, after;
   pid_t pid;
   int status;
   int ws = 0;

   DENTER(TOP_LAYER, "sge_edit");;

   if (fname == NULL) {
      ERROR((SGE_EVENT, MSG_NULLPOINTER));
      return -1;
   }

   if (SGE_STAT(fname, &before)) {
      ERROR((SGE_EVENT, MSG_FILE_EDITFILEXDOESNOTEXIST_S, fname));
      DEXIT;
      return -1;
   }

   chown(fname, myuid, mygid);

   pid = fork();
   if (pid) {
      while (ws != pid) {
         ws = waitpid(pid, &status, 0);
         if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
               ERROR((SGE_EVENT, MSG_QCONF_EDITOREXITEDWITHERROR_I,
                      (int) WEXITSTATUS(status)));
               DEXIT;
               return -1;
            }
            else {
               if (SGE_STAT(fname, &after)) {
                  ERROR((SGE_EVENT, MSG_QCONF_EDITFILEXNOLONGEREXISTS_S, fname));
                  DEXIT;
                  return -1;
               }
               if ((before.st_mtime != after.st_mtime) ||
                    (before.st_size != after.st_size)) {
                  DEXIT;
                  return 0;
               }
               else {

                  DEXIT;
                  return 1;
               }
            }
         }
#ifndef WIN32
         if (WIFSIGNALED(status)) {
            ERROR((SGE_EVENT, MSG_QCONF_EDITORWASTERMINATEDBYSIGX_I,
                   (int) WTERMSIG(status)));
            DEXIT;
            return -1;
         }
#endif
      }
   } else {
      const char *cp = NULL;

      sge_set_def_sig_mask(NULL, NULL);
      sge_unblock_all_signals();
      setuid(getuid());
      setgid(getgid());

      cp = sge_getenv("EDITOR");
      if (!cp || strlen(cp) == 0)
         cp = DEFAULT_EDITOR;

      execlp(cp, cp, fname, (char *) 0);
      ERROR((SGE_EVENT, MSG_QCONF_CANTSTARTEDITORX_S, cp));
      SGE_EXIT(NULL, 1);
   }

   DEXIT;
   return (-1);
}
