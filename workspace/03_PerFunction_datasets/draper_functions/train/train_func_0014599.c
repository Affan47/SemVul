getParamType(char* tc)
{
    if (!tc) {
        return TYPE_ERROR;
    }
    if (strcmp(tc,"int")==0) {
        return TYPE_INT;
    }
    if (strcmp(tc,"uint")==0) {
        return TYPE_UINT;
    }
    if (strcmp(tc,"double")==0) {
        return TYPE_DOUBLE;
    }
    if (strcmp(tc,"bool")==0) {
        return TYPE_BOOL;
    }
    if (strcmp(tc,"string")==0) {
        return TYPE_STRING;
    }
    return TYPE_ERROR;
}
