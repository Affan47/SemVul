scanNamedChar() {
    if (U_FAILURE(*fStatus)) {
        return 0;
    }

    nextChar(fC);
    if (fC.fChar != chLBrace) {
        error(U_REGEX_PROPERTY_SYNTAX);
        return 0;
    }

    UnicodeString  charName;
    for (;;) {
        nextChar(fC);
        if (fC.fChar == chRBrace) {
            break;
        }
        if (fC.fChar == -1) {
            error(U_REGEX_PROPERTY_SYNTAX);
            return 0;
        }
        charName.append(fC.fChar);
    }

    char name[100];
    if (!uprv_isInvariantUString(charName.getBuffer(), charName.length()) ||
         (uint32_t)charName.length()>=sizeof(name)) {


        error(U_REGEX_PROPERTY_SYNTAX);
        return 0;
    }
    charName.extract(0, charName.length(), name, sizeof(name), US_INV);

    UChar32  theChar = u_charFromName(U_UNICODE_CHAR_NAME, name, fStatus);
    if (U_FAILURE(*fStatus)) {
        error(U_REGEX_PROPERTY_SYNTAX);
    }

    nextChar(fC);
    return theChar;
}
