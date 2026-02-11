sliderChange( SliderChange change )
{
    if ( change == SliderValueChange && isSliderDown() && signalsBlocked() )
    {
        int d = value() - m_formerValue;
        if ( d && d < 33 && d > -33 )
        {
            if ( d > 5 )
                d = 5;
            else if ( d < -5 )
                d = -5;
            m_formerValue += d;
            blockSignals( false );
            emit sliderMoved( m_formerValue );
            emit valueChanged( m_formerValue );
            blockSignals( true );
        }
        if ( d )
            setValue( m_formerValue );
    }
    QDial::sliderChange(change);
}
