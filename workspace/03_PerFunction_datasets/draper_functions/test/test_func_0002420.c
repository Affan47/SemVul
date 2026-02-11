enumerate_bitset_print(char* arr, unsigned len, llong offset)
{
    int ret = 0;
    unsigned count = len << 3;

    for (unsigned i = 0; i < count; ++i)
    {
        if (bitset_get(arr, i) != 0)
        {
            ++ret;
            printf("%lu\n", i + offset);
        }
    }

    return ret;
}
