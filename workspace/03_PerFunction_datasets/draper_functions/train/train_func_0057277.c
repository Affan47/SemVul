FuncIO_localtime( Obj self, Obj time )
{
    Obj tmp;
    time_t t;
    struct tm *s;
    if (!IS_INTOBJ(time)) {
        tmp = QuoInt(time,INTOBJ_INT(256));
        if (!IS_INTOBJ(tmp)) return Fail;
        t = INT_INTOBJ(tmp)*256 + INT_INTOBJ(ModInt(time,INTOBJ_INT(256)));
    } else t = INT_INTOBJ(time);
    s = localtime(&t);
    if (s == NULL) return Fail;
    tmp = NEW_PREC(0);
    AssPRec(tmp, RNamName("tm_sec"), INTOBJ_INT(s->tm_sec));
    AssPRec(tmp, RNamName("tm_min"), INTOBJ_INT(s->tm_min));
    AssPRec(tmp, RNamName("tm_hour"), INTOBJ_INT(s->tm_hour));
    AssPRec(tmp, RNamName("tm_mday"), INTOBJ_INT(s->tm_mday));
    AssPRec(tmp, RNamName("tm_mon"), INTOBJ_INT(s->tm_mon));
    AssPRec(tmp, RNamName("tm_year"), INTOBJ_INT(s->tm_year));
    AssPRec(tmp, RNamName("tm_wday"), INTOBJ_INT(s->tm_wday));
    AssPRec(tmp, RNamName("tm_yday"), INTOBJ_INT(s->tm_yday));
    AssPRec(tmp, RNamName("tm_isdst"), INTOBJ_INT(s->tm_isdst));
    return tmp;
}
