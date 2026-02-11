uplug_callPlug(UPlugData *plug, UPlugReason reason, UErrorCode *status) {
  UPlugTokenReturn token;
  if(plug==NULL||U_FAILURE(*status)) {
    return;
  }
  token = (*(plug->entrypoint))(plug, reason, status);
  if(token!=UPLUG_TOKEN) {
    *status = U_INTERNAL_PROGRAM_ERROR;
  }
}
