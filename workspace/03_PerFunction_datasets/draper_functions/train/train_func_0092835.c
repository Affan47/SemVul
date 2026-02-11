next(int32_t uchar) {
    const UChar *pos=pos_;
    if(pos==NULL) {
        return USTRINGTRIE_NO_MATCH;
    }
    int32_t length=remainingMatchLength_;
    if(length>=0) {

        if(uchar==*pos++) {
            remainingMatchLength_=--length;
            pos_=pos;
            int32_t node;
            return (length<0 && (node=*pos)>=kMinValueLead) ?
                    valueResult(node) : USTRINGTRIE_NO_VALUE;
        } else {
            stop();
            return USTRINGTRIE_NO_MATCH;
        }
    }
    return nextImpl(pos, uchar);
}
