format_msg (const ACE_TCHAR host_name[],
                            u_long verbose_flag,
                            ACE_TCHAR *verbose_msg)
{


  ACE_TCHAR timestamp[27];


#if defined (ACE_WIN32) || !defined (ACE_USES_WCHAR)
  const ACE_TCHAR *verbose_fmt =      ACE_TEXT ("%s@%s@%u@%s@%s");
  const ACE_TCHAR *verbose_lite_fmt = ACE_TEXT ("%s@%s@%s");
#else
  const ACE_TCHAR *verbose_fmt = ACE_TEXT ("%ls@%ls@%u@%ls@%ls");
  const ACE_TCHAR *verbose_lite_fmt = ACE_TEXT ("%ls@%ls@%ls");
#endif

  if (ACE_BIT_ENABLED (verbose_flag,
                       ACE_Log_Msg::VERBOSE)
      || ACE_BIT_ENABLED (verbose_flag,
                          ACE_Log_Msg::VERBOSE_LITE))
    {
      ACE_Time_Value reftime (this->secs_, this->usecs_);
      if (0 == ACE::timestamp (reftime,
                               timestamp,
                               sizeof (timestamp) / sizeof (ACE_TCHAR)))
        return -1;


      timestamp[23] = '\0';
    }

  if (ACE_BIT_ENABLED (verbose_flag,
                       ACE_Log_Msg::VERBOSE))
    {
      const ACE_TCHAR *lhost_name = ((host_name == 0)
                                      ? ACE_TEXT ("<local_host>")
                                      : host_name);
      ACE_OS::sprintf (verbose_msg,
                       verbose_fmt,
                       timestamp,
                       lhost_name,
                       this->pid_,
                       ACE_Log_Record::priority_name (ACE_Log_Priority (this->type_)),
                       this->msg_data_);
    }
  else if (ACE_BIT_ENABLED (verbose_flag, ACE_Log_Msg::VERBOSE_LITE))
    ACE_OS::sprintf (verbose_msg,
                     verbose_lite_fmt,
                     timestamp,
                     ACE_Log_Record::priority_name (ACE_Log_Priority (this->type_)),
                     this->msg_data_);
  else
    ACE_OS::strcpy (verbose_msg, this->msg_data_);
  return 0;
}
