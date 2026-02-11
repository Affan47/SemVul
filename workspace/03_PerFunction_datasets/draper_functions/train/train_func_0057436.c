next(const char *s, int32_t sLength) {
    if(sLength<0 ? *s==0 : sLength==0) {

        return current();
    }
    const uint8_t *pos=pos_;
    if(pos==NULL) {
        return USTRINGTRIE_NO_MATCH;
    }
    int32_t length=remainingMatchLength_;
    for(;;) {


        int32_t inByte;
        if(sLength<0) {
            for(;;) {
                if((inByte=*s++)==0) {
                    remainingMatchLength_=length;
                    pos_=pos;
                    int32_t node;
                    return (length<0 && (node=*pos)>=kMinValueLead) ?
                            valueResult(node) : USTRINGTRIE_NO_VALUE;
                }
                if(length<0) {
                    remainingMatchLength_=length;
                    break;
                }
                if(inByte!=*pos) {
                    stop();
                    return USTRINGTRIE_NO_MATCH;
                }
                ++pos;
                --length;
            }
        } else {
            for(;;) {
                if(sLength==0) {
                    remainingMatchLength_=length;
                    pos_=pos;
                    int32_t node;
                    return (length<0 && (node=*pos)>=kMinValueLead) ?
                            valueResult(node) : USTRINGTRIE_NO_VALUE;
                }
                inByte=*s++;
                --sLength;
                if(length<0) {
                    remainingMatchLength_=length;
                    break;
                }
                if(inByte!=*pos) {
                    stop();
                    return USTRINGTRIE_NO_MATCH;
                }
                ++pos;
                --length;
            }
        }
        for(;;) {
            int32_t node=*pos++;
            if(node<kMinLinearMatch) {
                UStringTrieResult result=branchNext(pos, node, inByte);
                if(result==USTRINGTRIE_NO_MATCH) {
                    return USTRINGTRIE_NO_MATCH;
                }

                if(sLength<0) {
                    if((inByte=*s++)==0) {
                        return result;
                    }
                } else {
                    if(sLength==0) {
                        return result;
                    }
                    inByte=*s++;
                    --sLength;
                }
                if(result==USTRINGTRIE_FINAL_VALUE) {

                    stop();
                    return USTRINGTRIE_NO_MATCH;
                }
                pos=pos_;
            } else if(node<kMinValueLead) {

                length=node-kMinLinearMatch;
                if(inByte!=*pos) {
                    stop();
                    return USTRINGTRIE_NO_MATCH;
                }
                ++pos;
                --length;
                break;
            } else if(node&kValueIsFinal) {

                stop();
                return USTRINGTRIE_NO_MATCH;
            } else {

                pos=skipValue(pos, node);

                U_ASSERT(*pos<kMinValueLead);
            }
        }
    }
}
