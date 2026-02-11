accumulateOutputSimpleMono(CompiledFlowInputPtr input,
                           CompiledFlowOutputPtr output)
{
    AuUint32 i;
    AuInt16 *in = (AuInt16 *) input->flowEl->minibuf;
#ifndef OUTPUT_RANGE_CHECK
    AuInt16 *out = (AuInt16 *) output->flowEl->minibuf;
    AuInt32 multiplyConstant = input->multiplyConstant;
#else
    AuInt32 multiplyConstantInteger,
            multiplyConstantFraction,
            *out = (AuInt32 *) output->flowEl->minibuf;

    multiplyConstantInteger =
            AuFixedPointIntegralAddend(input->multiplyConstant);
    multiplyConstantFraction =
            AuFixedPointFractionalAddend(input->multiplyConstant);
#endif

    in = (AuInt16 *) input->flowEl->minibuf;

    for (i = 0; i < input->flowEl->minibufSamples; i++)
#ifndef OUTPUT_RANGE_CHECK
        *out++ += (*in++ * multiplyConstant) >> 16;
#else
    {
        *out++ += (*in * multiplyConstantInteger) +
                ((*in * multiplyConstantFraction) >> 16);
        in++;
    }
#endif
}
