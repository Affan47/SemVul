get_minimum_bitsize (int (*read_pixel)(int pos, unsigned char *data),
                     int size, unsigned char *data)
{
    int i, max = 0, b = 2;
    for (i = 0; i < size; i++)
    {
        int c = read_pixel (i, data);
        if (c > max)
            max = c;
    }
    while ((1 << b) <= max)
    {
        b++;
    }
    return b;
}
