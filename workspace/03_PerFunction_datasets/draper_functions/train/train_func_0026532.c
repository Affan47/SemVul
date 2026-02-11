js_AtomizeDouble(JSContext *cx, jsdouble d)
{
    JSAtomState *state;
    JSDHashTable *table;
    JSAtomHashEntry *entry;
    uint32 gen;
    jsdouble *key;
    jsval v;

    state = &cx->runtime->atomState;
    table = &state->doubleAtoms;

    JS_LOCK(cx, &state->lock);
    entry = TO_ATOM_ENTRY(JS_DHashTableOperate(table, &d, JS_DHASH_ADD));
    if (!entry)
        goto failed_hash_add;
    if (entry->keyAndFlags == 0) {
        gen = ++table->generation;
        JS_UNLOCK(cx, &state->lock);

        key = js_NewWeaklyRootedDouble(cx, d);
        if (!key)
            return NULL;

        JS_LOCK(cx, &state->lock);
        if (table->generation == gen) {
            JS_ASSERT(entry->keyAndFlags == 0);
        } else {
            entry = TO_ATOM_ENTRY(JS_DHashTableOperate(table, key,
                                                       JS_DHASH_ADD));
            if (!entry)
                goto failed_hash_add;
            if (entry->keyAndFlags != 0)
                goto finish;
            ++table->generation;
        }
        INIT_ATOM_ENTRY(entry, key);
    }

  finish:
    v = DOUBLE_TO_JSVAL((jsdouble *)ATOM_ENTRY_KEY(entry));
    cx->weakRoots.lastAtom = v;
    JS_UNLOCK(cx, &state->lock);

    return (JSAtom *)v;

  failed_hash_add:
    JS_UNLOCK(cx, &state->lock);
    JS_ReportOutOfMemory(cx);
    return NULL;
}
