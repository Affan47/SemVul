drawNeedle( QPainter *painter,
    double length, QPalette::ColorGroup colorGroup ) const
{
    if ( d_style == ThinStyle )
    {
        const double width = qMax( length / 6.0, 3.0 );

        const int colorOffset = 10;

        const QColor light = palette().color( colorGroup, QPalette::Light );
        const QColor dark = palette().color( colorGroup, QPalette::Dark );

        qwtDrawShadedPointer( painter,
            dark.light( 100 + colorOffset ),
            dark.dark( 100 + colorOffset ),
            length, width );

        painter->rotate( 180.0 );

        qwtDrawShadedPointer( painter,
            light.light( 100 + colorOffset ),
            light.dark( 100 + colorOffset ),
            length, width );

        const QBrush baseBrush = palette().brush( colorGroup, QPalette::Base );
        drawKnob( painter, width, baseBrush, true );
    }
    else
    {
        qwtDrawTriangleNeedle( painter, palette(), colorGroup, length );
    }
}
