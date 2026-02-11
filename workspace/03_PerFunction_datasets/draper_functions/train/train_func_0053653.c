xml_defineProperty(JSContext *cx, JSObject *obj, jsid id, jsval value,
                   JSPropertyOp getter, JSPropertyOp setter, uintN attrs)
{
    if (VALUE_IS_FUNCTION(cx, value) || getter || setter ||
        (attrs & JSPROP_ENUMERATE) == 0 ||
        (attrs & (JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_SHARED))) {
        return js_DefineProperty(cx, obj, id, value, getter, setter, attrs);
    }

    return PutProperty(cx, obj, ID_TO_VALUE(id), &value);
}
