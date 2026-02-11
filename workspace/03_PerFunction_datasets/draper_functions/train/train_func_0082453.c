HTTP_get_value_for_key(
  char*       val,
  const int   max_val_len,
  const char* keybuf,
  const char* pbuf,
  const long  pbuf_len
)
{
  int         found = false;
  const int   keylen = strlen( keybuf );
  long        i, j;

  for( i=0; i < pbuf_len - keylen; ++i )
  {
    found = true;
    for( j=0; j<keylen; ++j )
    {
      if( toupper( keybuf[j] ) != toupper( pbuf[i+j] ) )
      {
        found = false;
        break;
      }
    }

    if( found && ( pbuf[i+j]==':' ) )
    {
      strncpy( val, & pbuf[i+j+1], max_val_len );
      val[max_val_len-1] = '\0';
      _http_trim( val, max_val_len );
      break;
    }
  }

  if(!found)
  {
    val[0]='\0';
    return false;
  }
  else
  {
    return true;
  }
}
