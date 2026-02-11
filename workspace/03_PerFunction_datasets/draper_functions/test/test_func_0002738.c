js_NewDoubleInRootedValue(JSContext *cx, jsdouble d, jsval *vp)
{
#ifdef JS_GCMETER
    JSGCArenaStats *astats;
#endif
    JSGCDoubleCell *cell;


    METER(astats = &cx->runtime->gcStats.doubleArenaStats);
    METER(astats->alloc++);
    cell = cx->doubleFreeList;
    if (!cell) {
        cell = RefillDoubleFreeList(cx);
        if (!cell) {
            METER(astats->fail++);
            return JS_FALSE;
        }
    } else {
        METER(astats->localalloc++);
    }
    cx->doubleFreeList = cell->link;
    cell->number = d;
    *vp = DOUBLE_TO_JSVAL(&cell->number);
    return JS_TRUE;
}
