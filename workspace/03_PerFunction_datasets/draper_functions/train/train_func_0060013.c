bufrsize(char * hold, fortint leng, fortint * holdsize,
                     fortint (*fileRead)(), void * stream)


{
unsigned char * phold = (unsigned char *) hold;
fortint numread, hsize = *holdsize;
fortint num, length;
fortint next, next_sec = 3;


  if ( leng < 24 ) return USER_BUFFER_TINY;
  num = 24;
  if ( hsize < num) {
    numread = fileRead( hold + hsize, num - hsize, stream);
    if ( numread <= 0 ) {
      *holdsize -= numread;
      return *holdsize;
    }
    hsize = num;
  }
  *holdsize = hsize;


  if ( hold[7] > 1 ) return THREE_BYTE_LONG(phold+4);


  length = SECT_0_LEN + THREE_BYTE_LONG(phold+4);
  if ( leng < (length+4) ) return USER_BUFFER_TINY;
  if ( hsize < (length+4)) {
    numread = fileRead( hold+hsize, (length+4)-hsize, stream);
    if ( numread <= 0 ) {
      *holdsize -= numread;
      return *holdsize;
    }
    hsize = length + 4;
    *holdsize = hsize;
  }


  if ( hold[11] & WMOBIT1 ) next_sec = 2;


  for ( next = next_sec; next < 5 ; next++ ) {
    length += THREE_BYTE_LONG(phold+length);
    if ( leng < (length+4) ) return USER_BUFFER_TINY;
    if ( hsize < (length+4)) {
      numread = fileRead( hold+hsize,(length+4)-hsize, stream);
      if ( numread <= 0 ) {
        *holdsize -= numread;
        return *holdsize;
      }
      hsize = length + 4;
      *holdsize = hsize;
    }
  }


  length += LEN_7777;
  if ( leng < length ) return USER_BUFFER_TINY;

  return length;

}
