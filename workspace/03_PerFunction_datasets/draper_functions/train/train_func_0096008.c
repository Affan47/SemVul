toUTF8(const char* sourceStart, const char* sourceEnd, Ice::UTF8Buffer& buffer) const
{
    size_t size = static_cast<size_t>(sourceEnd - sourceStart);
    Ice::Byte* targetStart = buffer.getMoreBytes(size, 0);
    Ice::Byte* targetEnd = targetStart + size;

    unsigned int j = size;
    for(unsigned int i = 0; i < size; ++i)
    {
        targetStart[i] = sourceStart[--j];
    }

    return targetEnd;
}
