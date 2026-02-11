Read_String (Object port, int konst) {
    register FILE *f;
    register int n, c, oc, str;

    Read_Reset ();
    f = PORT(port)->file;
    str = PORT(port)->flags & P_STRING;
    while (1) {
        Reader_Getc;
        if (c == EOF) {
eof:
            Reader_Tweak_Stream;
            Reader_Error (port, "end of file in string");
        }
        if (c == '\\') {
            Reader_Getc;
            switch (c) {
            case EOF: goto eof;
            case 'b': c = '\b'; break;
            case 't': c = '\t'; break;
            case 'r': c = '\r'; break;
            case 'n': c = '\n'; break;
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
                oc = n = 0;
                do {
                    oc <<= 3; oc += c - '0';
                    Reader_Getc;
                    if (c == EOF) goto eof;
                } while (Octal (c) && ++n <= 2);
                Reader_Ungetc;
                c = oc;
            }
        } else if (c == '"')
            break;
        Read_Store (c);
    }
    return General_Make_String (Read_Buf, Read_Size, konst);
}
