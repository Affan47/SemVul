rrpc_globuserr(char *errmsg, int len, globus_result_t r)

{
  globus_object_t	*eo;
  char			*s;

  if ((eo = globus_error_get(r)) == NULL)
    strncpy(errmsg, "Unknown globus error", len);
  else {
    s = globus_error_print_friendly(eo);
    globus_object_free(eo);
    if (s) {
      strncpy(errmsg, s, len);
      globus_libc_free(s);
    } else
      strncpy(errmsg, "Unknown globus error", len);
  }
  return GLOBUS_RLS_GLOBUSERR;
}
