setDown( bool down )
{
    if ( down == d_data->isDown )
        return;

    d_data->isDown = down;
    update();

    if ( d_data->itemMode == QwtLegend::ClickableItem )
    {
        if ( d_data->isDown )
            Q_EMIT pressed();
        else
        {
            Q_EMIT released();
            Q_EMIT clicked();
        }
    }

    if ( d_data->itemMode == QwtLegend::CheckableItem )
        Q_EMIT checked( d_data->isDown );
}
