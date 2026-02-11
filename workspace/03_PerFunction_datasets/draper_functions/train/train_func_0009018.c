linkName(s)
String s; {
    Name n = findName(findText(s));
    if (isNull(n)) {
        ERRMSG(0) "Prelude does not define standard name \"%s\"", s
        EEND;
    }
    return n;
}
