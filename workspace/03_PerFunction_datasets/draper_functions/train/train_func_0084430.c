ucol_addLatinOneEntry(UCollator *coll, UChar ch, uint32_t CE,
                    int32_t *primShift, int32_t *secShift, int32_t *terShift)
{
    uint8_t primary1 = 0, primary2 = 0, secondary = 0, tertiary = 0;
    UBool reverseSecondary = FALSE;
    UBool continuation = isContinuation(CE);
    if(!continuation) {
        tertiary = (uint8_t)((CE & coll->tertiaryMask));
        tertiary ^= coll->caseSwitch;
        reverseSecondary = TRUE;
    } else {
        tertiary = (uint8_t)((CE & UCOL_REMOVE_CONTINUATION));
        tertiary &= UCOL_REMOVE_CASE;
        reverseSecondary = FALSE;
    }

    secondary = (uint8_t)((CE >>= 8) & UCOL_BYTE_SIZE_MASK);
    primary2 = (uint8_t)((CE >>= 8) & UCOL_BYTE_SIZE_MASK);
    primary1 = (uint8_t)(CE >> 8);

    if(primary1 != 0) {
        if (coll->leadBytePermutationTable != NULL && !continuation) {
            primary1 = coll->leadBytePermutationTable[primary1];
        }

        coll->latinOneCEs[ch] |= (primary1 << *primShift);
        *primShift -= 8;
    }
    if(primary2 != 0) {
        if(*primShift < 0) {
            coll->latinOneCEs[ch] = UCOL_BAIL_OUT_CE;
            coll->latinOneCEs[coll->latinOneTableLen+ch] = UCOL_BAIL_OUT_CE;
            coll->latinOneCEs[2*coll->latinOneTableLen+ch] = UCOL_BAIL_OUT_CE;
            return;
        }
        coll->latinOneCEs[ch] |= (primary2 << *primShift);
        *primShift -= 8;
    }
    if(secondary != 0) {
        if(reverseSecondary && coll->frenchCollation == UCOL_ON) {
            coll->latinOneCEs[coll->latinOneTableLen+ch] >>= 8;
            coll->latinOneCEs[coll->latinOneTableLen+ch] |= (secondary << 24);
        } else {
            coll->latinOneCEs[coll->latinOneTableLen+ch] |= (secondary << *secShift);
        }
        *secShift -= 8;
    }
    if(tertiary != 0) {
        coll->latinOneCEs[2*coll->latinOneTableLen+ch] |= (tertiary << *terShift);
        *terShift -= 8;
    }
}
