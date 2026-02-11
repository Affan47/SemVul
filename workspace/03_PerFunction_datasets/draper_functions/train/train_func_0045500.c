makeExceptions() {
    uint32_t *row;
    uint32_t value;
    int32_t i;
    uint16_t excIndex;

    i=0;
    while((row=upvec_getRow(pv, i, NULL, NULL))!=NULL) {
        value=*row;
        if(value&UCASE_EXCEPTION) {
            excIndex=makeException(value, excProps+(value>>UGENCASE_EXC_SHIFT));
            *row=(value&~(UGENCASE_EXC_MASK|UCASE_EXC_MASK))|(excIndex<<UCASE_EXC_SHIFT);
        }
        ++i;
    }
}
