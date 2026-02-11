JS_CompileFileHandleForPrincipals(JSContext *cx, JSObject *obj,
                                  const char *filename, FILE *file,
                                  JSPrincipals *principals)
{
    uint32 tcflags;
    JSScript *script;

    CHECK_REQUEST(cx);
    tcflags = JS_OPTIONS_TO_TCFLAGS(cx);
    script = JSCompiler::compileScript(cx, obj, NULL, principals, tcflags,
                                       NULL, 0, file, filename, 1);
    LAST_FRAME_CHECKS(cx, script);
    return script;
}
