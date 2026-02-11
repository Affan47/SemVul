libsmtp_part_query(struct libsmtp_session_struct *libsmtp_session)
{

  if ((libsmtp_session->Stage < LIBSMTP_HEADERS_STAGE) ||
      (libsmtp_session->Stage > LIBSMTP_BODY_STAGE))
  {
    libsmtp_session->ErrorCode = LIBSMTP_BADSTAGE;
    return NULL;
  }


  if (!libsmtp_session->PartNow)
  {


    if (!libsmtp_session->Parts)
    {

      libsmtp_session->ErrorCode=LIBSMTP_NOPARENT;
      return NULL;
    }


    if (libsmtp_int_nextpart (libsmtp_session))
      return NULL;
  }


  return libsmtp_session->PartNow;
}
