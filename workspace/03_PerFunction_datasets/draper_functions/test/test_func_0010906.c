build_path(
int type
) {
   SGE_STRUCT_STAT statbuf;
   char *path, *base;
   char *postfix, *name, *job_id, *job_name, *ja_task_id;
   int pathlen;
   char err_str[SGE_PATH_MAX+128];

   switch (type) {
   case SGE_PAR_STDOUT:
      name = "pe_stdout_path";
      postfix = "po";
      break;
   case SGE_PAR_STDERR:
      name = "pe_stderr_path";
      postfix = "pe";
      break;
   case SGE_STDOUT:
      name = "stdout_path";
      postfix = "o";
      break;
   case SGE_STDERR:
      name = "stderr_path";
      postfix = "e";
      break;
   case SGE_STDIN:
      name = "stdin_path";
      postfix = "i";
      break;
   default:
      return NULL;
   }

   base = get_conf_val(name);


   if( SGE_STAT(base, &statbuf)) {

      if (errno != ENOENT) {
         char *t;
         sprintf(err_str, "can't stat() \"%s\" as %s: %s",
            base, name, strerror(errno));
         sprintf(err_str+strlen(err_str), " KRB5CCNAME=%s uid="uid_t_fmt" gid="uid_t_fmt" ",
                 (t=getenv("KRB5CCNAME"))?t:"none", getuid(), getgid());
         {
            gid_t groups[10];
            int i, ngid;
            ngid = getgroups(10, groups);
            for(i=0; i<ngid; i++)
               sprintf(err_str+strlen(err_str), uid_t_fmt" ", groups[i]);
         }
         shepherd_state = SSTATE_OPEN_OUTPUT;
         shepherd_error(1, err_str);
      }
      return base;
   }

   if( !(S_ISDIR(statbuf.st_mode))) {
      return base;
   } else {

      if (type == SGE_STDIN) {
         shepherd_state = SSTATE_OPEN_OUTPUT;
         shepherd_error(1, SFQ" is a directory not a file", base);
         return "/dev/null";
      } else {
         job_name = get_conf_val("job_name");
         job_id = get_conf_val("job_id");
         ja_task_id = get_conf_val("ja_task_id");

         if (!(path = (char *)malloc(pathlen=(strlen(base) + strlen(job_name)
                       + strlen(job_id) + strlen(ja_task_id) + 25)))) {
            shepherd_error(1, "malloc(%d) failed for %s@", pathlen, name);
         }

         if (atoi(ja_task_id)) {
            sprintf(path, "%s/%s.%s%s.%s", base, job_name, postfix, job_id,
               ja_task_id);
         } else {
            sprintf(path, "%s/%s.%s%s", base, job_name, postfix, job_id);
         }
      }
   }

   return path;
}
