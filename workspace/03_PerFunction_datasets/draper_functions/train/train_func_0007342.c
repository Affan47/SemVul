mostly_text(const char *data, size_t data_size)
{
    size_t          bin;
    size_t          j;

    bin = 0;
    for (j = 0; j < data_size; ++j)
    {
        unsigned char c = data[j];
        if (!c)
            return 0;
        if (!isprint(c) && !isspace(c))
            ++bin;
    }
    return (bin * 4 < data_size);
}
