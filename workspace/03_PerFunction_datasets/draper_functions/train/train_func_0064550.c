tokensAtRow( int row )
{
    DEBUG_BLOCK;

    int lower = 0;
    int upper = (int)rows();
    if( row > -1 && row < (int)rows() )
    {
        lower = row;
        upper = row + 1;
    }

    QList< Token *> list;
    Token *token;
    for( row = lower; row < upper; ++row )
        if ( QHBoxLayout *rowBox = qobject_cast<QHBoxLayout*>( layout()->itemAt( row )->layout() ) )
        {
            for( int col = 0; col < rowBox->count() - m_horizontalStretch; ++col )
                if ( ( token = qobject_cast<Token*>( rowBox->itemAt( col )->widget() ) ) )
                    list << token;
        }

    debug() << "Row:"<<row<<"items:"<<list.count();

    return list;
}
