TranslateGerman(void)


{
    char cThis;

    cThis = getTexChar();

    switch (cThis) {
        case 'a':
            fprintRTF("\\'e4");
            break;
        case 'o':
            fprintRTF("\\'f6");
            break;
        case 'u':
            fprintRTF("\\'fc");
            break;
        case 's':
            fprintRTF("\\'df");
            break;
        case 'A':
            fprintRTF("\\'c4");
            break;
        case 'O':
            fprintRTF("\\'d6");
            break;
        case 'U':
            fprintRTF("\\'dc");
            break;
        case '|':
            break;
        case '-':
            break;
        case '"':
            break;
        case '\'':
            fprintRTF("\\ldblquote ");
            break;
        case '`':
            fprintRTF("{\\'84}");
            break;
        case '<':
            fprintRTF("\\'ab");
            break;
        case '>':
            fprintRTF("\\'bb");
            break;
        default:
            fprintRTF("%c", cThis);
    }
}
