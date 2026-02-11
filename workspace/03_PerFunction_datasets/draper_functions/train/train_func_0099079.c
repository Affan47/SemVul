insertComboText( const QString &text )
{
    if( text.isEmpty() )
        return;

    if( m_search->contains( text ) )
    {
        m_search->setCurrentIndex( m_search->findText( text ) );
        return;
    }
    m_search->completionObject()->addItem( text );
    m_search->insertItem( 0, KStandardGuiItem::find().icon(), text );
    m_search->setCurrentIndex( 0 );
}
