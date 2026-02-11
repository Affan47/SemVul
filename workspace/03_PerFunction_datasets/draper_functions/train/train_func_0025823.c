CmdDotChar(int code)
{
    int n = RtfFontNumber("STIXGeneral");
    char *cParam = getBraceParam();

    switch (cParam[0]) {
        case 'A':
            fprintRTF("\\u550A");
            break;
        case 'a':
            fprintRTF("\\u551a");
            break;
        case 'C':
            fprintRTF("\\u266C");
            break;
        case 'c':
            fprintRTF("\\u267c");
            break;
        case 'E':
            fprintRTF("\\u278E");
            break;
        case 'e':
            fprintRTF("\\u279e");
            break;
        case 'G':
            fprintRTF("\\u288G");
            break;
        case 'g':
            fprintRTF("\\u289g");
            break;
        case 'I':
            fprintRTF("\\u304I");
            break;
        case 'O':
            fprintRTF("\\u558O");
            break;
        case 'o':
            fprintRTF("\\u559o");
            break;
        case 'Z':
            fprintRTF("\\u379Z");
            break;
        case 'z':
            fprintRTF("\\u380z");
            break;
        case '\0':
            putUnicodeChar(0x02,0xD9,'.');
            break;
        default:
            fprintRTF("{\\f%d",n);
            fprintRTF("\\u775.}");
            ConvertString(cParam);
            break;
    }

    free(cParam);
}
