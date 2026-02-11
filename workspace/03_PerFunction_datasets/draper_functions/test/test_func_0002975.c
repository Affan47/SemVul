japi_open_session(const char *username, const char* unqualified_hostname, const char *key_in, dstring *key_out, dstring *diag)
{
#ifdef ENABLE_PERSISTENT_JAPI_SESSIONS
   struct passwd pw_struct, *pwd;
   char buffer[2048];
   char tmp_session_path_buffer[SGE_PATH_MAX];
   dstring tmp_session_path;
#endif

   DENTER(TOP_LAYER, "japi_open_session");

   if (key_in == NULL) {
      char tmp_session_key_buffer[SGE_PATH_MAX];
      dstring tmp_session_key;
      unsigned int id = 0;


      id = sge_get_gmt();

      sge_dstring_init(&tmp_session_key, tmp_session_key_buffer, sizeof(tmp_session_key_buffer));


      id = rand_r((unsigned int *)&id);


      sge_dstring_sprintf(&tmp_session_key, "%s."pid_t_fmt".%.6d",
                          unqualified_hostname, getpid(),
                          id);

      DPRINTF(("created new session using generated \"%s\" as JAPI session key\n",
               sge_dstring_get_string(&tmp_session_key)));
      sge_dstring_copy_dstring(key_out, &tmp_session_key);
   } else {
      sge_dstring_copy_string(key_out, key_in);
   }

   DRETURN(DRMAA_ERRNO_SUCCESS);
}
