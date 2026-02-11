half2single(uint16_t number)
{
    uint32_t fp32;
    uint32_t s = number>>15;
    uint32_t e = (number>>10)&0x01F;


    if(e==0)
        e=15-127;
    if (e==0x1F)
    {
        if (number&0x03FF)
            fp32 = 0x7FC00000;
        else
            fp32 = s?0xFF800000:0x7F800000;
    }
    else
        fp32 = (s<<31) | ((e+127-15)<<23) | ((number&0x3ff)<<13);

    return *(float*)&fp32;
}
