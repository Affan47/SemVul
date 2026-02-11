CmdTildeChar(int code)
{
    int n = RtfFontNumber("STIXGeneral");
    char *cParam = getBraceParam();

    if (strstr(cParam, "\\i")) {
        fprintRTF("\\u297i");
        free(cParam);
        return;
    }

    switch (cParam[0]) {
        case 'A':
            fprintRTF("\\'c3");
            break;
        case 'O':
            fprintRTF("\\'d5");
            break;
        case 'a':
            fprintRTF("\\'e3");
            break;
        case 'o':
            fprintRTF("\\'f5");
            break;
        case 'n':
            fprintRTF("\\'f1");
            break;
        case 'N':
            fprintRTF("\\'d1");
            break;
        case 'I':
            fprintRTF("\\u296I");
            break;
        case 'U':
            fprintRTF("\\u360U");
            break;
        case 'u':
            fprintRTF("\\u361u");
            break;
        case '\0':
            fprintRTF("\\'7e");
            break;
        default:
            fprintRTF("{\\f%d",n);
            fprintRTF("\\u771\\'7e}");
            ConvertString(cParam);
            break;
    }

    free(cParam);
}
