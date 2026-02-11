_zero_padded(unsigned long num, int width)
{
    int n = 1;
    while (num /= 10L)
        n++;
    return width > n ? width - n : 0;
}
