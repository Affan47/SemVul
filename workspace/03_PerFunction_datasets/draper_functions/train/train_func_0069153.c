isValidDigitString(const UnicodeString& str) {

    StringCharacterIterator it(str);
    UChar32 c;
    UChar32 prev = 0;
    int32_t i = 0;

    for ( it.setToStart(); it.hasNext(); ) {
       c = it.next32PostInc();
       if ( c > 0xFFFF ) {
          return FALSE;
       }
       i++;
       prev = c;
    }
    return TRUE;
}
