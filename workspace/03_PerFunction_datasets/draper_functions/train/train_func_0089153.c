quotedString(ExecState* exec, const UString& string)
{

    if (m_state != Success)
        return UString();

    if (exec->hadException()) {
        m_state = FailedException;
        return UString();
    }

    const int size = string.size();
    UString ret = "\"";

    for (int i = 0; i < size; ++i) {
        int start = i;
        static const short unsigned blackSlashUC = '\\';
        static const short unsigned quoteUC = '\"';
        while (i < size && (string[i].uc > 0x001F && string[i].uc != blackSlashUC && string[i].uc != quoteUC))
            ++i;
        ret += string.substr(start, i-start);

        if (i >= size)
            break;

        switch (string[i].uc) {
            case '\t':
                ret += "\\t";
                break;
            case '\r':
                ret += "\\r";
                break;
            case '\n':
                ret += "\\n";
                break;
            case '\f':
                ret += "\\f";
                break;
            case '\b':
                ret += "\\b";
                break;
            case '"':
                ret += "\\\"";
                break;
            case '\\':
                ret += "\\\\";
                break;
            default:
                static const char hexDigits[] = "0123456789abcdef";
                short unsigned ch = string[i].uc;
                ret.append("\\u");
                ret.append(hexDigits[(ch >> 12) & 0xF]);
                ret.append(hexDigits[(ch >> 8) & 0xF]);
                ret.append(hexDigits[(ch >> 4) & 0xF]);
                ret.append(hexDigits[ch & 0xF]);
                break;
        }
    }

    ret.append('\"');
    return ret;
}
