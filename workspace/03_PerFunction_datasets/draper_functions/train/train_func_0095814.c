CompileRegExpToAST(JSContext* cx, JSTokenStream* ts,
                   JSString* str, uintN flags, CompilerState& state)
{
    uintN i;
    size_t len;

    len = str->length();

    state.context = cx;
    state.tokenStream = ts;
    state.cp = js_UndependString(cx, str);
    if (!state.cp)
        return JS_FALSE;
    state.cpbegin = state.cp;
    state.cpend = state.cp + len;
    state.flags = flags;
    state.parenCount = 0;
    state.classCount = 0;
    state.progLength = 0;
    state.treeDepth = 0;
    state.classBitmapsMem = 0;
    for (i = 0; i < CLASS_CACHE_SIZE; i++)
        state.classCache[i].start = NULL;

    if (len != 0 && (flags & JSREG_FLAT)) {
        state.result = NewRENode(&state, REOP_FLAT);
        if (!state.result)
            return JS_FALSE;
        state.result->u.flat.chr = *state.cpbegin;
        state.result->u.flat.length = len;
        state.result->kid = (void *) state.cpbegin;

        state.progLength += 1 + GetCompactIndexWidth(0)
                          + GetCompactIndexWidth(len);
        return JS_TRUE;
    }

    return ParseRegExp(&state);
}
