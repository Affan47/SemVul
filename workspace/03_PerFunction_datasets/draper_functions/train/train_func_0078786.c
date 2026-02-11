ucm_mappingType(UCMStates *baseStates,
                UCMapping *m,
                UChar32 codePoints[UCNV_EXT_MAX_UCHARS],
                uint8_t bytes[UCNV_EXT_MAX_BYTES]) {

    int32_t count=ucm_countChars(baseStates, bytes, m->bLen);
    if(count<1) {

        return -1;
    }


    if( m->uLen==1 && count==1 && m->f<=3 &&
        (baseStates->maxCharLength==1 ||
            !((m->f==2 && m->bLen==1) ||
              (m->f==1 && bytes[0]==0) ||
              (m->f<=1 && m->bLen>1 && bytes[0]==0)))
    ) {
        return 0;
    } else {
        return 1;
    }
}
