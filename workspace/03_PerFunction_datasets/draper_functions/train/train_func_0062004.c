addCombiningCP(uint32_t code, uint8_t flags) {
    uint32_t newEntry;
    uint16_t i;

    newEntry=code|((uint32_t)flags<<24);


    for(i=0; i<combineBackTop; ++i) {
        if(code==(combiningCPs[i]&0xffffff)) {

            if(newEntry==combiningCPs[i]) {
                return;
            }


            newEntry|=combiningCPs[i];
            if(i!=--combineBackTop) {
                uprv_memmove(combiningCPs+i, combiningCPs+i+1, (combineBackTop-i)*4);
            }
            if(i<combineBothTop) {
                --combineBothTop;
            }
            if(i<combineFwdTop) {
                --combineFwdTop;
            }
            break;
        }
    }


    if(combineBackTop>=sizeof(combiningCPs)/4) {
        fprintf(stderr, "error: gennorm combining code points - trying to use more than %ld units\n",
                (long)(sizeof(combiningCPs)/4));
        exit(U_MEMORY_ALLOCATION_ERROR);
    }


    flags=(uint8_t)(newEntry>>24);
    if(flags==1) {
        i=combineFwdTop++;
        ++combineBothTop;
    } else if(flags==3) {
        i=combineBothTop++;
    } else  {
        i=combineBackTop;
    }


    if(i<combineBackTop) {
        uprv_memmove(combiningCPs+i+1, combiningCPs+i, (combineBackTop-i)*4);
    }
    combiningCPs[i]=newEntry;


    ++combineBackTop;
}
