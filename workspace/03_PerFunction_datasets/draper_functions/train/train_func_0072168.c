convertGrayCodeToBinary(l_uint32 val)
{
l_uint32  shift;

    for (shift = 1; shift < 32; shift <<= 1)
        val ^= val >> shift;
    return val;
}
