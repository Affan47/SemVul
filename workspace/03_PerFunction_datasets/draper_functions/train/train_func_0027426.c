safe_strequal(char* str1, char* str2)
{
  if(str1 && str2)

    return (0 != Curl_raw_equal(str1, str2)) ? TRUE : FALSE;
  else

    return (!str1 && !str2) ? TRUE : FALSE;
}
