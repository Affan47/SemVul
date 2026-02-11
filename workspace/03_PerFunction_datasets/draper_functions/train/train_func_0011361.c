murmur_64_a ( const void *key, size_t length, uint64_t seed )
{
    const uint64_t m = 0xc6a4a7935bd1e995LL;
    const int r = 47;
    uint64_t h;
    uint64_t k;
    const uint64_t* data;
    const uint64_t* end;
    const unsigned char* data2;

    h = seed ^ length;
    data = (const uint64_t*)key;
    end = data + (length / 8);

    while (data != end)
    {
        k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    data2 = (const unsigned char*)data;
    switch (length & 7)
    {
        case 7: h ^= (uint64_t)(data[6]) << 48;
        case 6: h ^= (uint64_t)(data[5]) << 40;
        case 5: h ^= (uint64_t)(data[4]) << 32;
        case 4: h ^= (uint64_t)(data[3]) << 24;
        case 3: h ^= (uint64_t)(data[2]) << 16;
        case 2: h ^= (uint64_t)(data[1]) << 8;
        case 1: h ^= (uint64_t)(data[0]);
                h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}
