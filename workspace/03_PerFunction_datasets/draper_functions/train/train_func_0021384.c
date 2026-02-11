arg_type_from_int (const char *s)
{
    int i = atoi(s);

    switch (i) {
    case 1: return GRETL_TYPE_DOUBLE;
    case 2: return GRETL_TYPE_SERIES;
    case 3: return GRETL_TYPE_LIST;
    case 4: return GRETL_TYPE_MATRIX;
    case 5: return GRETL_TYPE_BOOL;
    case 6: return GRETL_TYPE_INT;
    case 7: return GRETL_TYPE_SCALAR_REF;
    case 8: return GRETL_TYPE_SERIES_REF;
    case 9: return GRETL_TYPE_MATRIX_REF;
    }

    return GRETL_TYPE_NONE;
}
