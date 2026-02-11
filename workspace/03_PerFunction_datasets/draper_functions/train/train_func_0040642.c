MTX_BITIO_ReadValue( BITIO *t, long numberOfBits )
{
    unsigned long value;
    long i;

    value = 0;
    for ( i = numberOfBits-1; i >=0; i-- ) {
        value <<= 1;
        if ( MTX_BITIO_input_bit(t) ) value |= 1;
    }
    return value;
}
