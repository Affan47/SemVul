hnj_hyphen_lhmin(int utf8, const char *word, int word_size, char * hyphens,
	char *** rep, int ** pos, int ** cut, int lhmin)
{
    int i = 1, j;


    if (utf8 && ((unsigned char) word[0] == 0xEF) && ((unsigned char) word[1] == 0xAC))  {
      i += hnj_ligature(word[2]);
    }


    for (j = 0; word[j] <= '9' && word[j] >= '0'; j++) i--;

    for (j = 0; i < lhmin && word[j] != '\0'; i++) do {

      if (*rep && *pos && *cut && (*rep)[j]) {
        char * rh = strchr((*rep)[j], '=');
        if (rh && (hnj_hyphen_strnlen(word, j - (*pos)[j] + 1, utf8) +
          hnj_hyphen_strnlen((*rep)[j], rh - (*rep)[j], utf8)) < lhmin) {
            free((*rep)[j]);
            (*rep)[j] = NULL;
            hyphens[j] = '0';
          }
       } else {
         hyphens[j] = '0';
       }
       j++;


       if (utf8 && ((unsigned char) word[j] == 0xEF) && ((unsigned char) word[j + 1] == 0xAC))  {
         i += hnj_ligature(word[j + 2]);
       }
    } while (utf8 && (word[j] & 0xc0) == 0x80);
    return 0;
}
