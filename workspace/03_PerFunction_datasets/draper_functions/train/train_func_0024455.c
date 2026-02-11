adjustState( double value )
{
    while ( value > 1.0 )
        value -= 1.0;
    while ( value < 0.0 )
        value += 1.0;
    return value;
}
