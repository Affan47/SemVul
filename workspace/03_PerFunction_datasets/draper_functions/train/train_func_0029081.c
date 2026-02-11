InitTempNSArray(JSContext *cx, JSTempRootedNSArray *tmp)
{
    XMLArrayInit(cx, &tmp->array, 0);
    tmp->value = JSVAL_NULL;
    JS_PUSH_TEMP_ROOT_TRACE(cx, trace_temp_ns_array, &tmp->tvr);
}
