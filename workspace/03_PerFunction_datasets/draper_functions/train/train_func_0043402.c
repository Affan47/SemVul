errorString(int errorcode, int syserror)
{

  static const char messages[] =
  {
    I18N_NOOP("no error")"\0"
    I18N_NOOP("requested family not supported for this host name")"\0"
    I18N_NOOP("temporary failure in name resolution")"\0"
    I18N_NOOP("non-recoverable failure in name resolution")"\0"
    I18N_NOOP("invalid flags")"\0"
    I18N_NOOP("memory allocation failure")"\0"
    I18N_NOOP("name or service not known")"\0"
    I18N_NOOP("requested family not supported")"\0"
    I18N_NOOP("requested service not supported for this socket type")"\0"
    I18N_NOOP("requested socket type not supported")"\0"
    I18N_NOOP("unknown error")"\0"
    I18N_NOOP2("1: the i18n'ed system error code, from errno",
	      "system error: %1")"\0"
    "\0"
  };

  static const int messages_indices[] = {
      0,    9,   59,   96,  139,  153,  179,  205,
      236,  289,  325,    0
  };


  if (errorcode == Canceled)
    return i18n("request was canceled");

  Q_ASSERT(int(SystemError) <= -(int)(sizeof(messages_indices)/sizeof(messages_indices[0])));
  if (errorcode > 0 || errorcode < SystemError)
    return QString();

  QString msg = i18n(messages + messages_indices[-errorcode]);
  if (errorcode == SystemError)
    msg.arg(QString::fromLocal8Bit(strerror(syserror)));

  return msg;
}
