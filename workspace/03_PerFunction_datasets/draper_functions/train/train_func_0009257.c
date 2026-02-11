___device_file_default_options_virt
   ___P((___device_stream *self),
        (self)
___device_stream *self;)
{
  int settings = ___setup_params.file_settings;
  int char_encoding_errors = ___CHAR_ENCODING_ERRORS(settings);
  int char_encoding = ___CHAR_ENCODING(settings);
  int eol_encoding = ___EOL_ENCODING(settings);
  int buffering = ___BUFFERING(settings);

  if (char_encoding_errors == 0)
    char_encoding_errors = ___CHAR_ENCODING_ERRORS_ON;

  if (char_encoding == 0)
    char_encoding = ___CHAR_ENCODING_ISO_8859_1;

  if (eol_encoding == 0)
    eol_encoding = ___EOL_ENCODING_LF;

#ifdef USE_WIN32

  if (buffering == 0)
    {
      ___device_file *d = ___CAST(___device_file*,self);

      if (GetFileType (d->h) == FILE_TYPE_PIPE)
        buffering = ___NO_BUFFERING;
      else
        buffering = ___FULL_BUFFERING;
    }

#else

  if (buffering == 0)
    buffering = ___FULL_BUFFERING;

#endif

#ifdef ___DEBUG

  ___printf ("file char_encoding_errors=%d   char_encoding=%d   eol_encoding=%d   buffering=%d\n",
             char_encoding_errors,
             char_encoding,
             eol_encoding,
             buffering);

#endif

  return ___FIX(___STREAM_OPTIONS(char_encoding_errors,
                                  char_encoding,
                                  eol_encoding,
                                  buffering,
                                  char_encoding_errors,
                                  char_encoding,
                                  eol_encoding,
                                  buffering));
}
