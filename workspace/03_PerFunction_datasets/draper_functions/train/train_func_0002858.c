jsv_get_pid(lListElem *jsv) {
   pid_t pid = -1;
   const char *pid_string = NULL;

   DENTER(TOP_LAYER, "jsv_get_pid");
   pid_string = lGetString(jsv, JSV_pid);
   if (pid_string != NULL) {
      sscanf(pid_string, pid_t_fmt, &pid);
   }
   DRETURN(pid);
}
