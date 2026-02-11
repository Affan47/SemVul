ucol_uprv_tok_readOption(const UChar *start, const UChar *end, const UChar **optionArg) {
    int32_t i = 0;
    ucol_uprv_tok_initData();

    while(PatternProps::isWhiteSpace(*start)) {
        start++;
    }
    while(i < UTOK_OPTION_COUNT) {
        if(u_strncmpNoCase(start, rulesOptions[i].optionName, rulesOptions[i].optionLen) == 0) {
            if(end - start > rulesOptions[i].optionLen) {
                *optionArg = start+rulesOptions[i].optionLen;
                while(PatternProps::isWhiteSpace(**optionArg)) {
                    (*optionArg)++;
                }
            }
            break;
        }
        i++;
    }
    if(i == UTOK_OPTION_COUNT) {
        i = -1;
    }
    return i;
}
