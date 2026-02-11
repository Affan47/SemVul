run()
{
    {

        QMutexLocker l( &(d->rendererMutex) );
        d->renderer();
    }

    foreach ( const QString & element, m_elementsToRender )
    {
        {
            QMutexLocker l( &m_haltMutex );
            if ( m_haltFlag )
                return;
        }

        QString key = keyForPixmap( element, m_size );
        if ( !d->cache->contains( key ) )
        {
            kDebug() << "Renderering" << key << "in rendering thread.";
            QImage img = d->renderCard( element, m_size );
            d->cache->insertImage( key, img );
            emit renderingDone( element, img );
        }
    }
}
