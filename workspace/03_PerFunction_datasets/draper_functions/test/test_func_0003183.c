in_typeclass(int tclass, int type) {
    if (tclass == T_INT) {
        return gm_is_long_type(type) || gm_is_int_type(type);
    }
    if (tclass == T_NUMERIC) {
        return gm_is_numeric_type(type);
    }
    if (tclass == T_NUMERIC_INF) {
        return gm_is_inf_type(type) || gm_is_numeric_type(type);
    }
    if (tclass == T_BOOL) {
        return gm_is_boolean_type(type);
    }
    assert(false);
    return false;
}
