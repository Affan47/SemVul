locale_write_ordinal_number_lang(char *buf, unsigned n, LanguageCode code, int number) {

  switch (code) {
    case LC_DE:

      snprintf( buf, n, "%d.", number);
      break;
    case LC_C:
    case LC_EN:
    default: {
      const int num100 = number % 100;
      switch ( num100 < 10 || num100 > 19 ? number % 10 : 4 ) {
        case 1: snprintf( buf, n, "%dst", number ); break;
        case 2: snprintf( buf, n, "%dnd", number ); break;
        case 3: snprintf( buf, n, "%drd", number ); break;
        default: snprintf( buf, n, "%dth", number ); break;
      }
      break;
    }
  }
}
