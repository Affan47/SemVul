Convert32To24Frame(const void* data, unsigned char* dest, unsigned npixels)
{
    const unsigned char* src = (const unsigned char*)data;

    #if defined(__x86_64) || defined(USE_MMX)
    while(npixels >= 8)
    {
        Convert32To24_32bytes(src, dest);
        src  += 4*8;
        dest += 3*8;
        npixels -= 8;
    }
     #ifdef USE_MMX
     MMX_clear();
     #endif
    #endif

    for(unsigned pos=0; pos<npixels; ++pos)
    {
        dest[3*pos+0] = src[4*pos+0];
        dest[3*pos+1] = src[4*pos+1];
        dest[3*pos+2] = src[4*pos+2];
    }
}
