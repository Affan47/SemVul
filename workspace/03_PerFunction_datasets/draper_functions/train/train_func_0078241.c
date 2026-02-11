charset_j2p(char *buf, int max_len, long char_set)
{
   switch (char_set) {
    case CHAR_SET_JAPANESE: Euc2Sjis(buf, max_len); break;
    case CHAR_SET_LATIN1  :  break;
    case CHAR_SET_1250    : Lat2Win(buf,max_len); break;
    case CHAR_SET_1251    : koi8_to_win1251(buf, max_len); break;
    case CHAR_SET_1251_B  : win1251_to_koi8(buf, max_len); break;
    default:
      UTF_to_other(buf, max_len);
      break;
   }
}
