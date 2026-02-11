js_GetExternalStringGCType(JSString *str)
{
    JS_ASSERT(!JSString::isStatic(str));

    uintN type = (uintN) *GetGCThingFlags(str) & GCF_TYPEMASK;
    JS_ASSERT(type == GCX_STRING || type >= GCX_EXTERNAL_STRING);
    return (type == GCX_STRING) ? -1 : (intN) (type - GCX_EXTERNAL_STRING);
}
