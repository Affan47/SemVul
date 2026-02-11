readAttributeValue (char &lastchar) {
    std::string value = "" ;
    char ch = skipSpaces() ;
    if (ch == '"') {
        while (!str.eof()) {
            char ch = get_char() ;
            if (ch == '"') {
                lastchar = get_char () ;
                break ;
            }
            value += ch ;
        }
    } else if (ch == '>') {
        throw XMLException ("Missing XML attribute value") ;
    } else {
        value += ch ;
        while (!str.eof()) {
            char ch = get_char() ;
            if (isspace(ch) || ch == '/' || ch == '>') {
                lastchar = ch ;
                break ;
            }
            value += ch ;
        }
    }
    lastchar = skipSpaces (lastchar) ;
    return value ;
}
