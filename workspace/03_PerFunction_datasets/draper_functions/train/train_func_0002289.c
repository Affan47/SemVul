setPen( const QPen &pen )
{
    if ( d_data->majPen != pen || d_data->minPen != pen )
    {
        d_data->majPen = pen;
        d_data->minPen = pen;
        itemChanged();
    }
}
