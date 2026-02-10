copyToEnd(std::ostream &out) {
    int startLevel = blockLevel++ ;
    std::istream &in = currentContext->getStream() ;
    readLine(false) ;
    while (!in.eof()) {
        char *s = line ;
        while (*s != 0) {
            if (*s == '{') {
                blockLevel++ ;
            } else if (*s == '}') {
                if (--blockLevel == startLevel) {
                    resetInput() ;
                    return ;
                }
            }
            out.put (*s++) ;
        }
        out.put ('\n') ;
        readLine (false) ;
    }
}
