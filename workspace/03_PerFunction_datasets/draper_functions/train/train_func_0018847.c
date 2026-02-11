copySpec(const UChar* spec) {
    int32_t len = 0;
    while (spec[len] != END) {
        ++len;
    }
    ++len;
    UChar *result = (UChar *)uprv_malloc(len*sizeof(UChar));

    if (result != NULL) {
    	uprv_memcpy(result, spec, len*sizeof(result[0]));
    }
    return result;
}
