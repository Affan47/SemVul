adjustLoc(YYLTYPE * loc, const char * s, size_t len)
{
    loc->first_line = loc->last_line;
    loc->first_column = loc->last_column;

    while (len--) {
       switch (*s++) {
       case '\r':
           if (*s == '\n')
               s++;

       case '\n':
           ++loc->last_line;
           loc->last_column = 1;
           break;
       default:
           ++loc->last_column;
       }
    }
}
