subsf (ExecState *exec, JSValue *index)
{
    if (!index->isNumber())
        return throwError(exec, TypeError,
                          SPREF"subs: expected number as first argument");

    int i = qRound(index->getNumber());
    if (i < 0 || i >= subs->size())
        return throwError(exec, RangeError,
                          SPREF"subs: index out of range");

    return jsString(subs->at(i));
}
