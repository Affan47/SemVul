setenv (const ACE_TCHAR *variable_name,
                             const ACE_TCHAR *format, ...)
{


  size_t const buflen = ACE_OS::strlen (variable_name) + ACE_OS::strlen (format) + 2;
  ACE_TCHAR *newformat = 0;
  ACE_NEW_RETURN (newformat, ACE_TCHAR[buflen], -1);
  ACE_Auto_Basic_Array_Ptr<ACE_TCHAR> safe_newformat (newformat);


  ACE_OS::sprintf (safe_newformat.get (),
                   ACE_TEXT ("%s=%s"),
                   variable_name,
                   format);


  va_list argp;
  va_start (argp, format);


  size_t tmp_buflen = buflen;
  if (DEFAULT_COMMAND_LINE_BUF_LEN > buflen)
    {
      tmp_buflen = DEFAULT_COMMAND_LINE_BUF_LEN;
    }
  int retval = 0;

  ACE_TCHAR *stack_buf = 0;
  ACE_NEW_RETURN (stack_buf, ACE_TCHAR[tmp_buflen], -1);
  ACE_Auto_Basic_Array_Ptr<ACE_TCHAR> safe_stack_buf (stack_buf);

  do
    {
      retval = ACE_OS::vsnprintf (safe_stack_buf.get (), tmp_buflen, safe_newformat.get (), argp);
      if (retval > ACE_Utils::truncate_cast<int> (tmp_buflen))
        {
          tmp_buflen *= 2;
          ACE_NEW_RETURN (stack_buf, ACE_TCHAR[tmp_buflen], -1);
          safe_stack_buf.reset (stack_buf);
        }
      else
        break;
    }
  while (1);

  if (retval == -1)
    {


      if (errno == ENOTSUP)
        {


          retval = ACE_OS::vsprintf (safe_stack_buf.get (), safe_newformat.get (), argp);
          if (retval == -1)

            return -1;
        }
      else

        return -1;
    }


  va_end (argp);


  if (this->setenv_i (safe_stack_buf.get (),
                      ACE_OS::strlen (safe_stack_buf.get ())) == -1)
    return -1;

#if defined (ACE_WIN32)
  if (inherit_environment_)
    this->inherit_environment ();
#endif

  return 0;
}
