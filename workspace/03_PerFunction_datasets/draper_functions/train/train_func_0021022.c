addToken( Token * token )
{
    token->setParent( this );
    token->setVisible( false );

    QListWidgetItem *item = new QListWidgetItem( token->icon(), token->name() );
    if( token->hasCustomColor() )
    {
        item->setData( Qt::ForegroundRole, token->textColor() );
        item->setToolTip( "<font color=\"" + token->textColor().name() + "\">" + token->name() + "</font>" );
    }
    else
    {
        item->setToolTip( token->name() );
    }
    addItem( item );

    token->setParent( this );
    token->hide();
    m_itemTokenMap.insert( item, token );
}
