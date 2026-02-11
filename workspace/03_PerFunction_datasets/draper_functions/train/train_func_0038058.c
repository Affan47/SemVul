setDeckContents( const QList<quint32> & ids )
{
    foreach ( KCard * c, d->cards )
        delete c;
    d->cards.clear();
    d->cardsWaitedFor.clear();

    QHash<QString,CardElementData> oldFrontIndex = d->frontIndex;
    d->frontIndex.clear();

    QHash<QString,CardElementData> oldBackIndex = d->backIndex;
    d->backIndex.clear();

    foreach ( quint32 id, ids )
    {
        KCard * c = new KCard( id, this );

        c->setObjectName( elementName( c->id() ) );

        connect( c, SIGNAL(animationStarted(KCard*)), d, SLOT(cardStartedAnimation(KCard*)) );
        connect( c, SIGNAL(animationStopped(KCard*)), d, SLOT(cardStoppedAnimation(KCard*)) );

        QString elementId = elementName( id, true );
        d->frontIndex[ elementId ].cardUsers.append( c );

        elementId = elementName( id, false );
        d->backIndex[ elementId ].cardUsers.append( c );

        d->cards << c;
    }

    QHash<QString,CardElementData>::iterator it;
    QHash<QString,CardElementData>::iterator end;
    QHash<QString,CardElementData>::const_iterator it2;
    QHash<QString,CardElementData>::const_iterator end2;

    end = d->frontIndex.end();
    end2 = oldFrontIndex.constEnd();
    for ( it = d->frontIndex.begin(); it != end; ++it )
    {
        it2 = oldFrontIndex.constFind( it.key() );
        if ( it2 != end2 )
            it.value().cardPixmap = it2.value().cardPixmap;
    }

    end = d->backIndex.end();
    end2 = oldBackIndex.constEnd();
    for ( it = d->backIndex.begin(); it != end; ++it )
    {
        it2 = oldBackIndex.constFind( it.key() );
        if ( it2 != end2 )
            it.value().cardPixmap = it2.value().cardPixmap;
    }
}
