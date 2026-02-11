count() const
{
    int c = 0;
    for( int row = rows() - 1; row >= 0; --row )
        if( QBoxLayout *box = qobject_cast<QBoxLayout*>( layout()->itemAt( row )->layout() ) )
            c += box->count() - m_horizontalStretch;

    return c;
}
