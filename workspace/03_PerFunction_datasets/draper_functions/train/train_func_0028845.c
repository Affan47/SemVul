setItemHighlight( QGraphicsItem * item, bool highlight )
    {
        KCard * card = qgraphicsitem_cast<KCard*>( item );
        if ( card )
        {
            card->setHighlighted( highlight );
            return;
        }

        KCardPile * pile = qgraphicsitem_cast<KCardPile*>( item );
        if ( pile )
        {
            pile->setHighlighted( highlight );
            return;
        }
    }
