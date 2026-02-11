setFadeOpacity( qreal value )
{
    setWindowOpacity( value * maxOpacity() );

    if( value == 0.0 )
    {
        QWidget::hide();
    }
}
