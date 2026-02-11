JS_MaybeGC(JSContext *cx)
{
    JSRuntime *rt;
    uint32 bytes, lastBytes;

    rt = cx->runtime;

#ifdef JS_GC_ZEAL
    if (rt->gcZeal > 0) {
        JS_GC(cx);
        return;
    }
#endif

    bytes = rt->gcBytes;
    lastBytes = rt->gcLastBytes;


    if ((bytes > 8192 && bytes > lastBytes + lastBytes / 3) ||
        rt->gcMallocBytes >= rt->gcMaxMallocBytes) {
        JS_GC(cx);
    }
}
