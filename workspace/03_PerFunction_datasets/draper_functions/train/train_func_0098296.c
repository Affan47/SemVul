do_in(MBState& s, const char* fromBegin, const char* fromEnd, const char*& fromNext,
                                   Char* toBegin, Char* toEnd, Char*& toNext) const
{
    Utf8Codec::result retstat = ok;
    fromNext = fromBegin;
    toNext = toBegin;

    while(fromNext < fromEnd) {
        uint8_t* fnext = (uint8_t *)(fromNext);

        if(toNext >= toEnd) {
            retstat = partial;
            break;
        }

        const size_t extraBytesToRead = trailingBytesForUTF8[*fnext];
        if(fromNext + extraBytesToRead >= fromEnd) {
            retstat = partial;
            break;
        }

        if( !isLegalUTF8( (const uint8_t*)fnext, extraBytesToRead + 1 ) ) {
            retstat = error;
            break;
        }

        *toNext = Char(0);
        switch (extraBytesToRead) {
            case 5: *toNext = Char((toNext->value() + *fnext++) << 6);
            case 4: *toNext = Char((toNext->value() + *fnext++) << 6);
            case 3: *toNext = Char((toNext->value() + *fnext++) << 6);
            case 2: *toNext = Char((toNext->value() + *fnext++) << 6);
            case 1: *toNext = Char((toNext->value() + *fnext++) << 6);
            case 0: *toNext = Char((toNext->value() + *fnext++));
        }
        *toNext = Char(toNext->value() - offsetsFromUTF8[extraBytesToRead]);


        if(*toNext > MaxLegalUtf32) {
            *toNext = ReplacementChar;
        }
        else if(*toNext >= SurHighStart && *toNext <= SurLowEnd) {
            *toNext = ReplacementChar;
        }

        ++toNext;
        fromNext += (extraBytesToRead + 1);
    }

    return retstat;
}
