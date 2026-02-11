tspGetOSInfo( const size_t len, char* buf )
{
  if( len > 0  &&  buf != NULL )
  {
#ifdef OS_UNAME_INFO
    snprintf( buf, len, "Built on ///%s///", OS_UNAME_INFO );
#else
    snprintf( buf, len, "Built on ///unknown UNIX/BSD/Linux version///" );
#endif
  }
}
