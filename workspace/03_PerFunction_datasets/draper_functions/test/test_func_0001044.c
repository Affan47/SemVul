setPenWidth(double penWidth)
{
    if ( penWidth < 0.0 )
        penWidth = 0.0;

    if ( d_data->penWidth != penWidth )
    {
        d_data->penWidth = penWidth;
        itemChanged();
    }
}
