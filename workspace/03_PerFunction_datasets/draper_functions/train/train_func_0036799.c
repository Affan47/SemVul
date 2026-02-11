get_realm_hash(request_rec *r, const char *user,
                                   const char *realm, char **rethash)
{
  int status;

  MP_TRACE_a(MP_FUNC,
             "Apache::AuthenHook - calling Digest handler\n");

  status = call_provider(r, "digest", user, realm, &*rethash);

  switch(status) {
    case AUTH_GENERAL_ERROR:
      ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "Apache::AuthenHook - yikes! something bad happened!");
      ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Apache::AuthenHook - try running with PerlTrace a");
      break;

    case OK:
      ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Apache::AuthenHook - user '%s', hash '%s' found in realm '%s'",
                    user, *rethash, realm);

      status = AUTH_USER_FOUND;
      break;

    case DECLINED:
      ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Apache::AuthenHook - passing user '%s' to next provider",
                    user);

      status = AUTH_USER_NOT_FOUND;
      break;

    default:
      ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Apache::AuthenHook - user '%s' in realm '%s' denied",
                    user, realm);

      status = AUTH_DENIED;
  };

  return status;
}
