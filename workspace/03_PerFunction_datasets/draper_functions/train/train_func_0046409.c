addCompletion( const QString &text )
{
    int index = m_sw->findText( text );
    if( index == -1 )
    {
        m_sw->addItem( KStandardGuiItem::find().icon(), text );
        m_sw->completionObject()->addItem( text );
    }

    index = m_sw->findText( text );
    m_sw->setCurrentIndex( index );
}
