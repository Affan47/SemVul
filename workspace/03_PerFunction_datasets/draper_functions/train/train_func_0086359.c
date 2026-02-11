paletteChanged( const QPalette &palette )
{
    const QString backgroundColor = PaletteHandler::highlightColor().name();
    const QString textColor = palette.color( QPalette::Active, QPalette::HighlightedText ).name();
    const QString linkColor = palette.color( QPalette::Active, QPalette::Link ).name();
    const QString ridgeColor = palette.color( QPalette::Active, QPalette::Window ).name();

    QString hintStyle( "QLabel { background-color: %1; color: %2; border-radius: 3px; } "
                       "a { color: %3; }" );
    hintStyle = hintStyle.arg( backgroundColor, textColor, linkColor );

    QString barStyle( "QFrame#PlaylistBarBox { border: 1px ridge %1; background-color: %2; "
                                             " color: %3; border-radius: 3px; } "
                      "QLabel { color: %4; }" );
    barStyle = barStyle.arg( ridgeColor, backgroundColor, textColor );

    m_dynamicHintWidget->setStyleSheet( hintStyle );
    if( m_barBox )
        m_barBox->setStyleSheet( barStyle );

}
