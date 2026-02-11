UpdateBigNumbers(BigNumber *bn0, ...)
{
    va_list v;
    BigNumber *bn;

    va_start(v, bn0);
    bn = bn0;
    while (bn)
    {
        UpdateData(bn->AsByteArray(), bn->GetNumBytes());
        bn = va_arg(v, BigNumber *);
    }
    va_end(v);
}
