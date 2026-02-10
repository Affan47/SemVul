ucm_countChars(UCMStates *states,
               const uint8_t *bytes, int32_t length) {
    uint32_t offset;
    int32_t i, entry, count;
    uint8_t state;

    offset=0;
    count=0;
    state=0;

    if(states->countStates==0) {
        fprintf(stderr, "ucm error: there is no state information!\n");
        return -1;
    }


    if(length==2 && states->outputType==MBCS_OUTPUT_2_SISO) {
        state=1;
    }


    for(i=0; i<length; ++i) {
        entry=states->stateTable[state][bytes[i]];
        if(MBCS_ENTRY_IS_TRANSITION(entry)) {
            state=(uint8_t)MBCS_ENTRY_TRANSITION_STATE(entry);
            offset+=MBCS_ENTRY_TRANSITION_OFFSET(entry);
        } else {
            switch(MBCS_ENTRY_FINAL_ACTION(entry)) {
            case MBCS_STATE_ILLEGAL:
                fprintf(stderr, "ucm error: byte sequence ends in illegal state\n");
                return -1;
            case MBCS_STATE_CHANGE_ONLY:
                fprintf(stderr, "ucm error: byte sequence ends in state-change-only\n");
                return -1;
            case MBCS_STATE_UNASSIGNED:
            case MBCS_STATE_FALLBACK_DIRECT_16:
            case MBCS_STATE_VALID_DIRECT_16:
            case MBCS_STATE_FALLBACK_DIRECT_20:
            case MBCS_STATE_VALID_DIRECT_20:
            case MBCS_STATE_VALID_16:
            case MBCS_STATE_VALID_16_PAIR:

                ++count;
                state=(uint8_t)MBCS_ENTRY_FINAL_STATE(entry);
                offset=0;
                break;
            default:

                fprintf(stderr, "ucm error: byte sequence reached reserved action code, entry: 0x%02lx\n", (unsigned long)entry);
                return -1;
            }
        }
    }

    if(offset!=0) {
        fprintf(stderr, "ucm error: byte sequence too short, ends in non-final state %u\n", state);
        return -1;
    }


    if(count>1 && states->outputType==MBCS_OUTPUT_2_SISO && length!=2*count) {
        fprintf(stderr, "ucm error: SI/SO (like EBCDIC-stateful) result with %d characters does not contain all DBCS\n", (int)count);
        return -1;
    }

    return count;
}
