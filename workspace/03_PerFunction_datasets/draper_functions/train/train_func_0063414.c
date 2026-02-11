ClosestPow2 (size_t x)
{
    if (!(x & (x - 1)))
        return x;
    while (x & (x + 1))
        x |= (x + 1);
    return x + 1;
}
