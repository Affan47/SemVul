resizeEvent( QResizeEvent *re )
{
    if( width() != height() )
        resize( height(), height() );
    else
        QDial::resizeEvent( re );

    if( re->size() != re->oldSize() )
    {
        renderIcons();
        m_sliderGradient = QPixmap( size() );
        updateSliderGradient();
        update();
    }
}
