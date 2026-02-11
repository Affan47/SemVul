next(UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) {
        return FALSE;
    }
    const UChar *pos=pos_;
    if(pos==NULL) {
        if(stack_->isEmpty()) {
            return FALSE;
        }


        int32_t stackSize=stack_->size();
        int32_t length=stack_->elementAti(stackSize-1);
        pos=uchars_+stack_->elementAti(stackSize-2);
        stack_->setSize(stackSize-2);
        str_.truncate(length&0xffff);
        length=(int32_t)((uint32_t)length>>16);
        if(length>1) {
            pos=branchNext(pos, length, errorCode);
            if(pos==NULL) {
                return TRUE;
            }
        } else {
            str_.append(*pos++);
        }
    }
    if(remainingMatchLength_>=0) {


        return truncateAndStop();
    }
    for(;;) {
        int32_t node=*pos++;
        if(node>=kMinValueLead) {
            if(skipValue_) {
                pos=skipNodeValue(pos, node);
                node&=kNodeTypeMask;
                skipValue_=FALSE;
            } else {

                UBool isFinal=(UBool)(node>>15);
                if(isFinal) {
                    value_=readValue(pos, node&0x7fff);
                } else {
                    value_=readNodeValue(pos, node);
                }
                if(isFinal || (maxLength_>0 && str_.length()==maxLength_)) {
                    pos_=NULL;
                } else {


                    pos_=pos-1;
                    skipValue_=TRUE;
                }
                return TRUE;
            }
        }
        if(maxLength_>0 && str_.length()==maxLength_) {
            return truncateAndStop();
        }
        if(node<kMinLinearMatch) {
            if(node==0) {
                node=*pos++;
            }
            pos=branchNext(pos, node+1, errorCode);
            if(pos==NULL) {
                return TRUE;
            }
        } else {

            int32_t length=node-kMinLinearMatch+1;
            if(maxLength_>0 && str_.length()+length>maxLength_) {
                str_.append(pos, maxLength_-str_.length());
                return truncateAndStop();
            }
            str_.append(pos, length);
            pos+=length;
        }
    }
}
