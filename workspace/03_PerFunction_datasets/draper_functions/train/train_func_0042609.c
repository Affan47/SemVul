toBool (const Value &v) {
    switch (v.type) {
    case T_NONE:
        return false;
    case T_INTEGER:
    case T_CHAR:
    case T_BOOL:
    case T_BYTE:
        return v.integer != 0;
    case T_STRING:
        return v.str->size() > 0;
    case T_VECTOR:
        return v.vec->size() > 0;
    case T_MAP:
        return v.m->size() > 0;
    default:
        return false;
    }
}
