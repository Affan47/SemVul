japi_get_contact(dstring *contact, dstring *diag)
{
   int japi_errno = DRMAA_ERRNO_SUCCESS;

   DENTER(TOP_LAYER, "japi_get_contact");

   if ((contact != NULL) && (diag != NULL)) {
      JAPI_LOCK_SESSION();
      if ((japi_session_key != NULL) &&
          (japi_session_key != JAPI_SINGLE_SESSION_KEY)) {
         sge_dstring_sprintf(contact, "session=%s", japi_session_key);
      }
      JAPI_UNLOCK_SESSION();
   }


   else if (contact == NULL) {
      japi_errno = DRMAA_ERRNO_INVALID_ARGUMENT;
      japi_standard_error(japi_errno, diag);
   }

   DRETURN(japi_errno);
}
