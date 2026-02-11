wxCountLines(const char* text, int scintillaMode)
{
    char eolchar;

    switch (scintillaMode) {
        case wxSCI_EOL_CRLF:
        case wxSCI_EOL_LF:
            eolchar = '\n';
            break;
        case wxSCI_EOL_CR:
            eolchar = '\r';
            break;
        default:
            return 0;
    }

    int count = 0;
    int i     = 0;
    while (text[i] != 0) {
        if (text[i] == eolchar) {
            count++;
        }
        i++;
    }

    return count;
}
