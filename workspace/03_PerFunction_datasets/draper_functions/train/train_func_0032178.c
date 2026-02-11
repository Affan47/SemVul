indic_nextSyllableBoundary(HB_Script script, const HB_UChar16 *s, int start, int end, bool *invalid)
{
    const HB_UChar16 *uc = s+start;
    int pos = 0;
    Form state = form(uc[pos]);

    *invalid = false;

    IDEBUG("indic_nextSyllableBoundary: start=%d, end=%d", start, end);

    IDEBUG("state[%d]=%d (uc=%4x)", pos, state, uc[pos]);
    pos++;

    if (state != Consonant && state != IndependentVowel) {
        if (state != Other)
            *invalid = true;
        goto finish;
    }

    while (pos < end - start) {
        Form newState = form(uc[pos]);
        IDEBUG("state[%d]=%d (uc=%4x)", pos, newState, uc[pos]);
        switch(newState) {
        case Control:
            newState = state;
 	    if (state == Halant && uc[pos] == 0x200d )
  		break;

            ++pos;
            goto finish;
        case Consonant:
	    if (state == Halant && (script != HB_Script_Sinhala || uc[pos-1] == 0x200d ))
                break;
            goto finish;
        case Halant:
            if (state == Nukta || state == Consonant)
                break;

            if (script == HB_Script_Bengali && pos == 1 &&
                 (uc[0] == 0x0985 || uc[0] == 0x098f))
                break;

            if (script == HB_Script_Sinhala && state == Matra) {
                ++pos;
                continue;
            }
            if (script == HB_Script_Malayalam && state == Matra && uc[pos-1] == 0x0d41) {
                ++pos;
                continue;
            }
            goto finish;
        case Nukta:
            if (state == Consonant)
                break;
            goto finish;
        case StressMark:
            if (state == VowelMark)
                break;

        case VowelMark:
            if (state == Matra || state == LengthMark || state == IndependentVowel)
                break;

        case Matra:
            if (state == Consonant || state == Nukta)
                break;
            if (state == Matra) {

                break;
            }


            if (script == HB_Script_Bengali && uc[pos] == 0x9be && uc[pos-1] == 0x985)
                break;
            if (script == HB_Script_Tamil && state == Matra) {
                if (uc[pos-1] == 0x0bc6 &&
                     (uc[pos] == 0xbbe || uc[pos] == 0xbd7))
                    break;
                if (uc[pos-1] == 0x0bc7 && uc[pos] == 0xbbe)
                    break;
            }
            goto finish;

        case LengthMark:
            if (state == Matra) {

                break;
            }
        case IndependentVowel:
        case Invalid:
        case Other:
            goto finish;
        }
        state = newState;
        pos++;
    }
 finish:
    return pos+start;
}
