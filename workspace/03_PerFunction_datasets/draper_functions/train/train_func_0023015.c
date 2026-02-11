AddAtomToArray(JSContext *cx, JSAtom *atom, JSIdArray *ida, jsint *ip)
{
    jsint i, length;

    i = *ip;
    length = ida->length;
    if (i >= length) {
        ida = SetIdArrayLength(cx, ida, JS_MAX(length * 2, 8));
        if (!ida)
            return NULL;
        JS_ASSERT(i < ida->length);
    }
    ida->vector[i] = ATOM_TO_JSID(atom);
    *ip = i + 1;
    return ida;
}
