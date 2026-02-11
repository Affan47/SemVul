widgetWheelEvent( QWheelEvent *wheelEvent )
{
    if ( pickRect().contains( wheelEvent->pos() ) )
        d_data->trackerPosition = wheelEvent->pos();
    else
        d_data->trackerPosition = QPoint( -1, -1 );

    updateDisplay();

    transition( wheelEvent );
}
