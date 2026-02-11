getString(const CharString &strings) const {
        int32_t offset=stringOffset;
        int32_t length;
        if(offset>=0) {
            length=(uint8_t)strings[offset++];
        } else {
            offset=~offset;
            length=((int32_t)(uint8_t)strings[offset]<<8)|(uint8_t)strings[offset+1];
            offset+=2;
        }
        return StringPiece(strings.data()+offset, length);
    }
