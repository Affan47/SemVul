xml_trace_vector(JSTracer *trc, JSXML **vec, uint32 len)
{
    uint32 i;
    JSXML *xml;

    for (i = 0; i < len; i++) {
        xml = vec[i];
        if (xml) {
            JS_SET_TRACING_INDEX(trc, "xml_vector", i);
            JS_CallTracer(trc, xml, JSTRACE_XML);
        }
    }
}
