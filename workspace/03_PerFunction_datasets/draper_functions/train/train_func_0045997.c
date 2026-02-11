cw_char_allowed(char c)
{

  c = toupper(c);


  tab_index = 0;
  while (cw_chars[tab_index].key != 0) {
    if (cw_chars[tab_index].key == c) {

      return TRUE;
    } else {
      tab_index++;
    }
  }

  return FALSE;
}
