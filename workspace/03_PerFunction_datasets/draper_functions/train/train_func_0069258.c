getHangulSyllableType(const IntProperty &, UChar32 c, UProperty ) {

    int32_t gcb=(int32_t)(u_getUnicodeProperties(c, 2)&UPROPS_GCB_MASK)>>UPROPS_GCB_SHIFT;
    if(gcb<LENGTHOF(gcbToHst)) {
        return gcbToHst[gcb];
    } else {
        return U_HST_NOT_APPLICABLE;
    }
}
