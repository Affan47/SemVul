applyPattern(const UnicodeString& newPattern, UErrorCode& status) {
    if (U_FAILURE(status)) {
        return;
    }
    this->pattern = newPattern;
    UnicodeString token;
    int32_t braceCount=0;
    fmtToken type;
    UBool spaceIncluded=FALSE;

    if (fParsedValuesHash==NULL) {
        fParsedValuesHash = new Hashtable(TRUE, status);
        if (U_FAILURE(status)) {
            return;
        }
        fParsedValuesHash->setValueDeleter(deleteHashStrings);
    }

    UBool getKeyword=TRUE;
    UnicodeString hashKeyword;
    UnicodeString *hashPattern;

    for (int32_t i=0; i<pattern.length(); ++i) {
        UChar ch=pattern.charAt(i);

        if ( !inRange(ch, type) ) {
            if (getKeyword) {
                status = U_ILLEGAL_CHARACTER;
                return;
            }
            else {
                token += ch;
                continue;
            }
        }
        switch (type) {
            case tSpace:
                if (token.length()==0) {
                    continue;
                }
                if (getKeyword) {

                    spaceIncluded = TRUE;
                }
                else {
                    token += ch;
                }
                break;
            case tLeftBrace:
                if ( getKeyword ) {
                    if (fParsedValuesHash->get(token)!= NULL) {
                        status = U_DUPLICATE_KEYWORD;
                        return;
                    }
                    if (token.length()==0) {
                        status = U_PATTERN_SYNTAX_ERROR;
                        return;
                    }
                    if (!pluralRules->isKeyword(token)) {
                        status = U_UNDEFINED_KEYWORD;
                        return;
                    }
                    hashKeyword = token;
                    getKeyword = FALSE;
                    token.remove();
                }
                else  {
                    if (braceCount==0) {
                        status = U_UNEXPECTED_TOKEN;
                        return;
                    }
                    else {
                        token += ch;
                    }
                }
                braceCount++;
                spaceIncluded = FALSE;
                break;
            case tRightBrace:
                if ( getKeyword ) {
                    status = U_UNEXPECTED_TOKEN;
                    return;
                }
                else  {
                    hashPattern = new UnicodeString(token);
                    fParsedValuesHash->put(hashKeyword, hashPattern, status);
                    if (U_FAILURE(status)) {
                        return;
                    }
                    braceCount--;
                    if ( braceCount==0 ) {
                        getKeyword=TRUE;
                        hashKeyword.remove();
                        hashPattern=NULL;
                        token.remove();
                    }
                    else {
                        token += ch;
                    }
                }
                spaceIncluded = FALSE;
                break;
            case tLetter:
            case tNumberSign:
                if (spaceIncluded) {
                    status = U_PATTERN_SYNTAX_ERROR;
                    return;
                }
            default:
                token+=ch;
                break;
        }
    }
    if ( checkSufficientDefinition() ) {
        return;
    }
    else {
        status = U_DEFAULT_KEYWORD_MISSING;
        return;
    }
}
