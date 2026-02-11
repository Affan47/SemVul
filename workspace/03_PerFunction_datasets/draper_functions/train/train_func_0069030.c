parse_number(unsigned char in[12])
{
    uint64_t size = 0;
    int i = 0;

    for (i = 0; i < 12; i++)
    {
        size *= 10;
        if (isdigit(in[i]))
            size += (in[i] - '0');
    }

    return size;
}
