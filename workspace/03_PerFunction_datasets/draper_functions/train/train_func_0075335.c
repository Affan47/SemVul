generator_trace(JSTracer *trc, JSObject *obj)
{
    JSGenerator *gen = (JSGenerator *) obj->getPrivate();
    if (!gen)
        return;


    JS_ASSERT_IF(gen->state != JSGEN_RUNNING && gen->state != JSGEN_CLOSING,
                 !gen->frame.down);


    js_TraceStackFrame(trc, &gen->frame);
}
