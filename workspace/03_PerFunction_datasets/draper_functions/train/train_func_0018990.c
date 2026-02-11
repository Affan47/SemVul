setPosition( double pos )
{
    if ( d_data->position != pos )
    {
        d_data->position = pos;
        d_data->borderDistance = -1;
        itemChanged();
    }
}
