js_SyncOptionsToVersion(JSContext* cx)
{
    if (cx->options & JSOPTION_XML)
        cx->version |= JSVERSION_HAS_XML;
    else
        cx->version &= ~JSVERSION_HAS_XML;
    if (cx->options & JSOPTION_ANONFUNFIX)
        cx->version |= JSVERSION_ANONFUNFIX;
    else
        cx->version &= ~JSVERSION_ANONFUNFIX;
}
