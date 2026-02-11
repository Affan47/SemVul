setAttribute( Attribute attribute, bool on )
{
    if ( bool( d_data->attributes & attribute ) != on )
    {
        if ( on )
            d_data->attributes |= attribute;
        else
            d_data->attributes &= ~attribute;

        if ( ( attribute == AtomicPainter ) && on )
            reset();
    }
}
