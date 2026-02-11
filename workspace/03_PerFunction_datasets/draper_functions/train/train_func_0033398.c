micro_untile_1_x_1_128bit(const void * src, unsigned src_pitch,
                                      void * dst, unsigned dst_pitch,
                                      unsigned width, unsigned height)
{
    unsigned i, j;
    const unsigned elem_size = 16;

    for (j = 0; j < height; ++j)
    {
        for (i = 0; i < width; ++i)
        {
            memcpy(dst, src, width * elem_size);
            dst += dst_pitch * elem_size;
            src += src_pitch * elem_size;
        }
    }
}
