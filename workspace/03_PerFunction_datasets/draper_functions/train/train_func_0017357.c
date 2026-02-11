setValue( double x, double y )
{
    if ( x != d_data->xValue || y != d_data->yValue )
    {
        d_data->xValue = x;
        d_data->yValue = y;
        itemChanged();
    }
}
