clamp(int i)
{
    if (static_cast<uint>(i) > 255)
        i = (((~i) >> 31) & 0xFF);

    return static_cast<uint8>(i);
}
