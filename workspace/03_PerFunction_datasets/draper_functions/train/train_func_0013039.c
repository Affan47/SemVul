_ShowEscape(buf, code, ior, prefix)
char *buf, *prefix;
int code, ior;
{
    char *bufp;

    if (prefix && *prefix) {
        strcpy(buf, prefix);
	strcat(buf, ": ");
        bufp = buf + strlen(buf);
    } else {
        bufp = buf;
    }
    if (code == -10) {
        snprintf(bufp,80, "Pascal system I/O error %d", ior);
        switch (ior) {
            case 3:
                strcat(buf, " (illegal I/O request)");
                break;
            case 7:
                strcat(buf, " (bad file name)");
                break;
            case FileNotFound:
                strcat(buf, " (file not found)");
                break;
            case FileNotOpen:
                strcat(buf, " (file not open)");
                break;
            case BadInputFormat:
                strcat(buf, " (bad input format)");
                break;
            case 24:
                strcat(buf, " (not open for reading)");
                break;
            case 25:
                strcat(buf, " (not open for writing)");
                break;
            case 26:
                strcat(buf, " (not open for direct access)");
                break;
            case 28:
                strcat(buf, " (string subscript out of range)");
                break;
            case EndOfFile:
                strcat(buf, " (end-of-file)");
                break;
            case FileWriteError:
		strcat(buf, " (file write error)");
		break;
        }
    } else {
        snprintf(bufp,80, "Pascal system error %d", code);
        switch (code) {
            case -2:
                strcat(buf, " (out of memory)");
                break;
            case -3:
                strcat(buf, " (reference to NIL pointer)");
                break;
            case -4:
                strcat(buf, " (integer overflow)");
                break;
            case -5:
                strcat(buf, " (divide by zero)");
                break;
            case -6:
                strcat(buf, " (real math overflow)");
                break;
            case -8:
                strcat(buf, " (value range error)");
                break;
            case -9:
                strcat(buf, " (CASE value range error)");
                break;
            case -12:
                strcat(buf, " (bus error)");
                break;
            case -20:
                strcat(buf, " (stopped by user)");
                break;
        }
    }
    return buf;
}
