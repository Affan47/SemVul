newFujiMn(uint16_t    tag,
                             IfdId       group,
                             IfdId       mnGroup,
                             const byte* ,
                             uint32_t    size,
                             ByteOrder   )
    {

        if (size < FujiMnHeader::sizeOfSignature() + 18) return 0;
        return newFujiMn2(tag, group, mnGroup);
    }
