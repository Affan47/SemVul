printToken (std::ostream &os, Token tok) {
    string s = findOperator (tok) ;
    if (s != "") {
       os << s ;
    } else {
       os << "unknown" ;
    }
}
