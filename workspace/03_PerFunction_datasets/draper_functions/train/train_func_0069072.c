getOperatorName() {
    string name = string ("operator") ;
    if (isOverloadableOperator (currentToken)) {
        switch (currentToken) {
        case LSQUARE:
            nextToken() ;
            nextToken() ;
            name += "[]" ;
            break ;
        case LBRACK:
            nextToken() ;
            nextToken() ;
            name += "()" ;
            break ;
        case SIZEOF:
            nextToken() ;
            name += " sizeof" ;
            break ;
        case TYPEOF:
            nextToken() ;
            name += " typeof" ;
            break ;
        case FOREACH:
            nextToken() ;
            name += " foreach" ;
            break ;
        case TIN:
            nextToken() ;
            name += " in" ;
            break ;
        case CAST:
            nextToken() ;
            name += " cast" ;
            break ;
        default:
            name += findOperator(currentToken) ;
            nextToken() ;
            break ;
        }
        return name ;
    } else if (currentToken == IDENTIFIER && spelling[0] == '.' && spelling[1] == '\0') {
        nextToken();
        return name + ".";
    } else {
        error ("Illegal operator overload") ;
        skipToEnd() ;
        return "" ;
    }
}
