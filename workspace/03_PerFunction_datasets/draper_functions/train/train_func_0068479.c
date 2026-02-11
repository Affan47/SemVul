putData(const unsigned char *d, size_t length)
{
    if (size < currentPos + length)
        setSize(currentPos + length);
    memcpy((unsigned char*)data + currentPos, d, length);
    currentPos += length;
    return length;
}
