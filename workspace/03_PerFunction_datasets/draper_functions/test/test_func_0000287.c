Int24_To_Int32(
    void *destinationBuffer, signed int destinationStride,
    void *sourceBuffer, signed int sourceStride,
    unsigned int count, struct PaUtilTriangularDitherGenerator *ditherGenerator )
{
    unsigned char *src  = (unsigned char*)sourceBuffer;
    PaInt32 *dest = (PaInt32*)  destinationBuffer;
    PaInt32 temp;

    (void) ditherGenerator;

    while( count-- )
    {

#if defined(PA_LITTLE_ENDIAN)
        temp = (((PaInt32)src[0]) << 8);
        temp = temp | (((PaInt32)src[1]) << 16);
        temp = temp | (((PaInt32)src[2]) << 24);
#elif defined(PA_BIG_ENDIAN)
        temp = (((PaInt32)src[0]) << 24);
        temp = temp | (((PaInt32)src[1]) << 16);
        temp = temp | (((PaInt32)src[2]) << 8);
#endif

        *dest = temp;

        src += sourceStride * 3;
        dest += destinationStride;
    }
}
