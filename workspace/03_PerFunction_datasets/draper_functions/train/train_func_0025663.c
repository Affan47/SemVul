seek_to(unsigned long absolute_position)
{
    const unsigned long tmppos = absolute_position < cardinality ? absolute_position : cardinality;
    seek( ELP_first );
    for (unsigned long i = 0; i < tmppos; i++)
        seek( ELP_next );
    return get( ELP_atpos );
}
