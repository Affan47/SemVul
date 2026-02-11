paintText( QPainter *p, const QColorGroup &cg )
{
    int textX = textRect( false ).x() + 2;
    int textY = textRect( false ).y();

    if ( isSelected() ) {
        p->fillRect( textRect( false ), cg.color( QPalette::Highlight ) );
        p->setPen( QPen( cg.color( QPalette::HighlightedText ) ) );
    } else {
        if ( iconView()->itemTextBackground() != Qt::NoBrush )
            p->fillRect( textRect( false ), iconView()->itemTextBackground() );
        p->setPen( cg.color( QPalette::Text ) );
    }

    int align = iconView()->itemTextPos() == Q3IconView::Bottom ? Qt::AlignHCenter : Qt::AlignLeft;
    m_wordWrap->drawText( p, textX, textY, align | KWordWrap::Truncate );
}
