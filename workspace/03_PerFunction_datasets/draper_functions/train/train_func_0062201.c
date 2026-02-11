iterator_trace(JSTracer *trc, JSObject *obj)
{


    JSObject *iterable = obj->getParent();
    if (!iterable) {

        return;
    }
    jsval iter_state = obj->fslots[JSSLOT_ITER_STATE];
    js_MarkEnumeratorState(trc, iterable, iter_state);
}
