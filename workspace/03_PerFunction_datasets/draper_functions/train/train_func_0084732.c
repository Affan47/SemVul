operator== (const Value &v) {
    switch (type) {
    case T_INTEGER: case T_BYTE:
    case T_CHAR: case T_BOOL:
        switch (v.type) {
        case T_INTEGER: case T_CHAR: case T_BYTE: case T_BOOL:
            return Value (integer == v.integer) ;

        case T_STRING:
            return Value (toString() == *v.str) ;

        case T_REAL:
            return Value ((double)integer == v.real) ;

        case T_VECTOR:
            break ;
        }
        break ;
    case T_REAL:
        switch (v.type) {
        case T_INTEGER: case T_CHAR: case T_BYTE: case T_BOOL:
            return Value (real == v.integer) ;

        case T_STRING:
            return Value (toString() == *v.str) ;

        case T_REAL:
            return Value (real == v.real) ;

        case T_VECTOR:
            break ;
        }
        break ;
    case T_STRING:
        switch (v.type) {
        case T_INTEGER: case T_CHAR: case T_REAL: case T_BYTE: case T_BOOL:
            return Value (*str == v.toString()) ;

        case T_STRING:
            return Value (*str == *v.str) ;

        case T_VECTOR:
            break ;
        }
        break ;

    case T_VECTOR:
        if (v.type == T_VECTOR) {
            return Value (*vec == *v.vec) ;
        }
        break ;

    case T_BYTEVECTOR:
        if (v.type == T_BYTEVECTOR) {
            return Value (*bytevec == *v.bytevec) ;
        }
        break ;

    case T_MAP:
        if (v.type == T_MAP) {
            return Value (*m == *v.m) ;
        }
        break ;

    case T_ENUMCONST:
        if (v.type == T_ENUMCONST) {
            return Value (ec->en == v.ec->en && ec->offset == v.ec->offset) ;
        }
        break ;

    case T_CLASS:
    case T_INTERFACE:
    case T_PACKAGE:
    case T_FUNCTION:
    case T_ENUM:
    case T_THREAD:
    case T_MONITOR:
        return block == v.block ;

    case T_OBJECT:
        return object == v.object ;

    case T_CLOSURE:
        return closure->block == v.closure->block ;
    }
    return Value (0) ;
}
