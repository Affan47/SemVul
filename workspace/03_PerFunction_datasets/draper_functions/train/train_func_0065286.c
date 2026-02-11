paintEvent( QPaintEvent*  )
{
    if ( m_image.isNull() )
        return;

    QPainter painter( this );
    painter.setRenderHint( QPainter::SmoothPixmapTransform );
    painter.setWorldTransform( worldTransform() );
    painter.drawImage( 0, 0, m_image );
}
