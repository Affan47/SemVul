delete_job(UAContext *ua)
{
   JobId_t JobId;
   char *s,*sep,*tok;

   int i = find_arg_with_value(ua, NT_("jobid"));
   if (i >= 0) {
      if (strchr(ua->argv[i], ',') != NULL || strchr(ua->argv[i], '-') != NULL) {
        s = bstrdup(ua->argv[i]);
        tok = s;


        sep = strchr(tok, ',');
        while (sep != NULL) {
           *sep = '\0';
           if (!delete_job_id_range(ua, tok)) {
              JobId = str_to_int64(tok);
              do_job_delete(ua, JobId);
           }
           tok = ++sep;
           sep = strchr(tok, ',');
        }

        if (!delete_job_id_range(ua, tok)) {
            JobId = str_to_int64(tok);
            do_job_delete(ua, JobId);
        }

         free(s);
      } else {
         JobId = str_to_int64(ua->argv[i]);
        do_job_delete(ua, JobId);
      }
   } else if (!get_pint(ua, _("Enter JobId to delete: "))) {
      return;
   } else {
      JobId = ua->int64_val;
      do_job_delete(ua, JobId);
   }
}
