as_char( long n ) const
{
    return the_values[n] > CHAR_MAX ? ncBad_char : (char) the_values[n];
}
