cmp_eq(void *a, numerictype_t atag, void *b, numerictype_t btag,
           int equalnans)
{
    union { double d; int64_t i64; } u, v;
    if (atag==btag && (!equalnans || atag < T_FLOAT))
        return cmp_same_eq(a, b, atag);

    double da = conv_to_double(a, atag);
    double db = conv_to_double(b, btag);

    if ((int)atag >= T_FLOAT && (int)btag >= T_FLOAT) {
        if (equalnans) {
            u.d = da; v.d = db;
            return u.i64 == v.i64;
        }
        return (da == db);
    }

    if (da != db)
        return 0;

    if (atag == T_UINT64) {


        if (btag == T_INT64) {
            return ((int64_t)*(uint64_t*)a == *(int64_t*)b);
        }
        else if (btag == T_DOUBLE) {
            return (*(uint64_t*)a == (uint64_t)(int64_t)*(double*)b);
        }
    }
    else if (atag == T_INT64) {
        if (btag == T_UINT64) {
            return (*(int64_t*)a == (int64_t)*(uint64_t*)b);
        }
        else if (btag == T_DOUBLE) {
            return (*(int64_t*)a == (int64_t)*(double*)b);
        }
    }
    else if (btag == T_UINT64) {
        if (atag == T_INT64) {
            return ((int64_t)*(uint64_t*)b == *(int64_t*)a);
        }
        else if (atag == T_DOUBLE) {
            return (*(uint64_t*)b == (uint64_t)(int64_t)*(double*)a);
        }
    }
    else if (btag == T_INT64) {
        if (atag == T_UINT64) {
            return (*(int64_t*)b == (int64_t)*(uint64_t*)a);
        }
        else if (atag == T_DOUBLE) {
            return (*(int64_t*)b == (int64_t)*(double*)a);
        }
    }
    return 1;
}
