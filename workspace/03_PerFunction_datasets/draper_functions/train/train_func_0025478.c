strsplit(char *s, unsigned int blanks, unsigned int width)
{

  unsigned int  i, j, k;
  unsigned int  cuti  = 0;
  unsigned int  cutj  = 0;
  unsigned int  limit = width;

  static char split[MAX_LENGTH];

  if (blanks >= width) {


    blanks = 0;
  }

  for (i = 0, j = 0; i < MAX_LENGTH && j < MAX_LENGTH; i++, j++) {

    split[j] = s[i];

    if (s[i] == ' ' || s[i] == '\0' || s[i] == '\n') {

      if (i > limit) {


        if (limit - cuti < width - blanks) {
          j = cutj;
          i = cuti;
        }
        else {
          if (s[i] == '\0')
            break;
        }


        split[j] = '\n';

        for (k = 0, j++; k < blanks && j < MAX_LENGTH; k++, j++) {
          split[j] = ' ';
        }
        j--;

        limit += width - blanks - (limit - i);
      }
      else {
        if (s[i] == '\0') break;
        if (s[i] == '\n') {


          i++;
          if (s[i] == '\0') {
            split[j] = '\0';
            break;
          }

          for (k = 0, j++; k < blanks && j < MAX_LENGTH; k++, j++) {
            split[j] = ' ';
          }
          j--;

          limit += width - blanks - (limit - i);
        }


        cutj = j;
        cuti = i;

      }
    }
  }


  split[MAX_LENGTH - 1] = '\0';

  return split;

}
