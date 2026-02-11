force_ijs_server_shutdown(COMM_HANDLE **phandle,
                              const char *this_component,
                              dstring *p_err_msg)
{
   int     ret;

   DENTER(TOP_LAYER, "force_ijs_server_shutdown");

   if (phandle == NULL || *phandle == NULL) {
      sge_dstring_sprintf(p_err_msg, "invalid connection handle");
      DPRINTF(("invalid connection handle - nothing to shut down\n"));
      DRETURN(1);
   }

   DPRINTF(("connection is still alive\n"));


   ret = comm_shutdown_connection(*phandle, COMM_CLIENT, g_hostname, p_err_msg);
   FREE(g_hostname);
   if (ret != COMM_RETVAL_OK) {
      DPRINTF(("comm_shutdown_connection() failed: %s (%d)\n",
               sge_dstring_get_string(p_err_msg), ret));
      ret = 2;
   } else {
      DPRINTF(("successfully shut down the connection\n"));
   }
   *phandle = NULL;

   DRETURN(ret);
}
