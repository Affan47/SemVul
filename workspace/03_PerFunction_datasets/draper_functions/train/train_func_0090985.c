Float32_To_Int8_DitherClip(
    void *destinationBuffer, signed int destinationStride,
    void *sourceBuffer, signed int sourceStride,
    unsigned int count, struct PaUtilTriangularDitherGenerator *ditherGenerator )
{
    float *src = (float*)sourceBuffer;
    signed char *dest =  (signed char*)destinationBuffer;
    (void)ditherGenerator;

    while( count-- )
    {
        float dither  = PaUtil_GenerateFloatTriangularDither( ditherGenerator );

        float dithered = (*src * (126.0f)) + dither;
        PaInt32 samp = (PaInt32) dithered;
        PA_CLIP_( samp, -0x80, 0x7F );
        *dest = (signed char) samp;

        src += sourceStride;
        dest += destinationStride;
    }
}
