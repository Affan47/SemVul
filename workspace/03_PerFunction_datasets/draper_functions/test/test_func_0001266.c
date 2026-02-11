JS_GetFrameThis(JSContext *cx, JSStackFrame *fp)
{
    JSStackFrame *afp;

    if (fp->flags & JSFRAME_COMPUTED_THIS)
        return fp->thisp;


    if (js_GetTopStackFrame(cx) != fp) {
        afp = cx->fp;
        if (afp) {
            afp->dormantNext = cx->dormantFrameChain;
            cx->dormantFrameChain = afp;
            cx->fp = fp;
        }
    } else {
        afp = NULL;
    }

    if (fp->argv)
        fp->thisp = js_ComputeThis(cx, JS_TRUE, fp->argv);

    if (afp) {
        cx->fp = afp;
        cx->dormantFrameChain = afp->dormantNext;
        afp->dormantNext = NULL;
    }

    return fp->thisp;
}
