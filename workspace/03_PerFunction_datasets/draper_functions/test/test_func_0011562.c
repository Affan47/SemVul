setHeader( const QString& header, const QFont& font )
{
    if ( m_itemsStartAt == 0 )
    {
        DragItem d;
        d.m_text = header;


        d.m_font = font;

        calcFontProperties( d, true );

        m_items.insert( 0, d );

        m_itemsStartAt = 1;
    }
    else
    {
        DragItem& d = m_items[0];
        d.m_text = header;
        d.m_font = font;
        calcFontProperties( d, true );
    }

    updateDragLabel();
}
