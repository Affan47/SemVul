generic_Constructor (JSContext* cx, uintN argc, jsval* vp)
{
  JSObject* obj = JS_NewObjectForConstructor (cx, vp);
  if (!obj) {
    JS_ReportError (cx, "Failed to create 'this' object");
    return JS_FALSE;
  }

  JS_SET_RVAL (cx, vp, OBJECT_TO_JSVAL (obj));
  return JS_TRUE;
}
