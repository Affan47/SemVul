updateBackground()
{
    QPalette palette;
    palette.setBrush( QPalette::Background, m_backgroundColor );

    setPalette( palette );
    setBackgroundRole( QPalette::Background );
    setAutoFillBackground( true );
}
