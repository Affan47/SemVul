shk_your(char *buf, struct obj *obj)
{
    if (!shk_owns(buf, obj) && !mon_owns(buf, obj))
            strcpy(buf, carried(obj) ? "your" : "the");
    return buf;
}
