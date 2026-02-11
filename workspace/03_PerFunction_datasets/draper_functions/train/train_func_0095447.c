readKeywordValue(char* line_buffer, char* keyword, char* buffer, int buffer_len)
{
  int strm_buf_len = strlen(line_buffer);
  char* strm_buf = new char[1 + strm_buf_len];

  strstream strm(strm_buf, 1 + strm_buf_len, ios::app);
  strm << line_buffer << ends;


  char* work_buf = new char[1 + strm_buf_len];
  char* tmp = work_buf;

  bool found = false;


  while ( !strm.eof() ) {


    strm.getline(tmp, strm_buf_len, ':');


    LibFront::trimLeft(tmp);


    if ( LibFront::ncEqualPartial(tmp, keyword) ) {
      found = true;


      tmp += strlen(keyword);


      reset(strm);
      strm << tmp << ends;
      break;
    }
  }

  if (!found)
    return false;


  strm.getline(tmp, strm_buf_len, ':');


  int len = strlen(tmp);
  while (len > 0 && tmp[len - 1] != ' ' )
    len--;
  tmp[len] = '\0';


  LibFront::trim(tmp);


  if ( strlen(tmp) <= buffer_len ) {
    strcpy(buffer, tmp);
    found = true;
  }
  else {
    found = false;
  }

  delete[] strm_buf;
  delete[] work_buf;

  return found;
}
