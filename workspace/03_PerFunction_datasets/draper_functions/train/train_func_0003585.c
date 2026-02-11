inf_session_get_sync_error_message(GQuark domain,
                                   guint code)
{
  if(domain == inf_session_sync_error_quark)
    return inf_session_sync_strerror(code);


  return _("An error with unknown error domain occured");
}
