operator[] (int i) const {
    switch (type) {
    case T_INTEGER: case T_CHAR: case T_BYTE: case T_BOOL:
        return Value (((UINTEGER)(integer & (1 << i))) >> i) ;

    case T_STRING:
        return Value ((char)(str->data()[i])) ;


    case T_VECTOR:
        return (*vec)[i] ;

    case T_BYTEVECTOR:
        return (*bytevec)[i] ;

    case T_ENUM:
        return Value (en->consts[i]) ;

    case T_NONE:
        return Value (0) ;
    }
}
