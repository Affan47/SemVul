parse()
{
    tchar c;
    pos = 0;
    while(pos < pattern.length()) {
        c = pattern[pos++];
        switch (state) {
        case LITERAL_STATE :

            if(pos == pattern.length()) {
                currentLiteral += c;
                continue;
            }
            if(c == ESCAPE_CHAR) {

                switch (pattern[pos]) {
                case ESCAPE_CHAR:
                    currentLiteral += c;
                    pos++;
                    break;
                default:
                    if(currentLiteral.length() != 0) {
                        list->push_back
                             (new LiteralPatternConverter(currentLiteral));


                    }
                    currentLiteral.resize(0);
                    currentLiteral += c;
                    state = CONVERTER_STATE;
                    formattingInfo.reset();
                }
            }
            else {
                currentLiteral += c;
            }
            break;

        case CONVERTER_STATE:
            currentLiteral += c;
            switch (c) {
            case LOG4CPLUS_TEXT('-'):
                formattingInfo.leftAlign = true;
                break;
            case LOG4CPLUS_TEXT('.'):
                state = DOT_STATE;
                break;
            default:
                if(c >= LOG4CPLUS_TEXT('0') && c <= LOG4CPLUS_TEXT('9')) {
                    formattingInfo.minLen = c - LOG4CPLUS_TEXT('0');
                    state = MIN_STATE;
                }
                else {
                    finalizeConverter(c);
                }
            }
            break;

        case MIN_STATE:
            currentLiteral += c;
            if (c >= LOG4CPLUS_TEXT('0') && c <= LOG4CPLUS_TEXT('9')) {
                formattingInfo.minLen = formattingInfo.minLen * 10 + (c - LOG4CPLUS_TEXT('0'));
            }
            else if(c == LOG4CPLUS_TEXT('.')) {
                state = DOT_STATE;
            }
            else {
                finalizeConverter(c);
            }
            break;

        case DOT_STATE:
            currentLiteral += c;
            if(c >= LOG4CPLUS_TEXT('0') && c <= LOG4CPLUS_TEXT('9')) {
                formattingInfo.maxLen = c - LOG4CPLUS_TEXT('0');
                state = MAX_STATE;
            }
            else {
                log4cplus::tostringstream buf;
                buf << LOG4CPLUS_TEXT("Error occured in position ")
                    << pos
                    << LOG4CPLUS_TEXT(".\n Was expecting digit, instead got char \"")
                    << c
                    << LOG4CPLUS_TEXT("\".");
                OFSTRINGSTREAM_GETOFSTRING(buf, str)
                getLogLog().error(str);
                state = LITERAL_STATE;
            }
            break;

         case MAX_STATE:
            currentLiteral += c;
            if (c >= LOG4CPLUS_TEXT('0') && c <= LOG4CPLUS_TEXT('9'))
                formattingInfo.maxLen = formattingInfo.maxLen * 10 + (c - LOG4CPLUS_TEXT('0'));
            else {
                finalizeConverter(c);
                state = LITERAL_STATE;
            }
            break;
        }
    }

    if(currentLiteral.length() != 0) {
        list->push_back(new LiteralPatternConverter(currentLiteral));

    }

    return list;
}
