parse_calendar_date(const char* s,
                               Int_token tab [5], double *sec)
{
    int i, waiting_separator, negative;

    negative = 0;
    waiting_separator = 0;
    i = 0;
    while (i < 5) {


        switch (*s) {
          case '\0':
              return i;

          case ' ' :
              s++;
              negative = 0;
              break;

          case '/' : case ':' : case '.' : case 'T' :
              if (waiting_separator) {
                  if ((*s == 'T') && (i != 3)) {


                      return -1;
                  }
                  s++;
                  negative = 0;
                  waiting_separator = 0;
              } else {
                  return -1;
              }
              break;

          case '-' :
              s++;
              if (waiting_separator) {
                  negative = 0;
                  waiting_separator = 0;
              } else if ((*s >= '0') && (*s <= '9')) {
                  negative = 1;
              } else {
                  return -1;
              }
              break;

          case '0' : case '1' : case '2' : case '3' : case '4' :
          case '5' : case '6' : case '7' : case '8' : case '9' :
              tab[i].value  = ((int) *s) - '0';
              tab[i].digits = 1;
              while (isdigit(*++s)) {
                  tab[i].value = tab[i].value*10 + (((int) *s) - '0');
                  tab[i].digits++;
              }
              if (negative) {
                  tab[i].value = -tab[i].value;
              }
              i++;
              negative = 0;
              waiting_separator = 1;
              break;

          default  :
              return -1;

        }

    }

    while (isspace(*s)) {
        s++;
    }
    if (*s == '\0') {
        return 5;
    }

    if ((*s == '/') || (*s == ':') || (*s == '.') || (*s == '-')) {

        s++;


        if (parse_float(s, sec, &s) == EXIT_SUCCESS) {
            while (isspace(*s)) {
                s++;
            }
            if (*s == '\0') {
                return 6;
            }
        }

    }


    return -1;

}
