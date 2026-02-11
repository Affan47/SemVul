DjVuWriteError( const char *message )
{
  G_TRY {
    GP<ByteStream> errout = ByteStream::get_stderr();
    if (errout)
      {
        const GUTF8String external = DjVuMessageLite::LookUpUTF8( message );
        errout->writestring(external+"\n");
      }


  } G_CATCH_ALL { } G_ENDCATCH;
}
