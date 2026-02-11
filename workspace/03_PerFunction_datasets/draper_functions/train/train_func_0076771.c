Float32_To_Int16(
    void *destinationBuffer, signed int destinationStride,
    void *sourceBuffer, signed int sourceStride,
    unsigned int count, struct PaUtilTriangularDitherGenerator *ditherGenerator )
{
    float *src = (float*)sourceBuffer;
    PaInt16 *dest =  (PaInt16*)destinationBuffer;
    (void)ditherGenerator;

    while( count-- )
    {
#ifdef PA_USE_C99_LRINTF
        float tempf = (*src * (32767.0f)) ;
        *dest = lrintf(tempf-0.5f);
#else
        short samp = (short) (*src * (32767.0f));
        *dest = samp;
#endif

        src += sourceStride;
        dest += destinationStride;
    }
}
