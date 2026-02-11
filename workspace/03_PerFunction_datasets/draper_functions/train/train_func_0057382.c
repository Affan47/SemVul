Int24_To_UInt8(
    void *destinationBuffer, signed int destinationStride,
    void *sourceBuffer, signed int sourceStride,
    unsigned int count, struct PaUtilTriangularDitherGenerator *ditherGenerator )
{
    unsigned char *src = (unsigned char*)sourceBuffer;
    unsigned char *dest = (unsigned char*)destinationBuffer;

    (void) ditherGenerator;

    while( count-- )
    {

#if defined(PA_LITTLE_ENDIAN)


        *dest = (unsigned char)(src[2] + 128);
#elif defined(PA_BIG_ENDIAN)
        *dest = (unsigned char)(src[0] + 128);


#endif

        src += sourceStride * 3;
        dest += destinationStride;
    }
}
