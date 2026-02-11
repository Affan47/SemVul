printHash(const Hash & hash)
{
    char buf[hash.hashSize * 2];
    for (unsigned int i = 0; i < hash.hashSize; i++) {
        buf[i * 2] = base16Chars[hash.hash[i] >> 4];
        buf[i * 2 + 1] = base16Chars[hash.hash[i] & 0x0f];
    }
    return string(buf, hash.hashSize * 2);
}
