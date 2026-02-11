JS_EncodeString(JSContext *cx, JSString *str)
{
    return js_DeflateString(cx, str->chars(), str->length());
}
