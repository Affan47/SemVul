ref( CachedObjectClient *c )
{
    CachedObject::ref(c);

#ifdef LOADER_DEBUG
    kDebug(6060) << "image" << this << "ref'd by client" << c;
#endif


    if ( m_status >= Persistent && !pixmap_size().isNull() ) {
#ifdef LOADER_DEBUG
        kDebug(6060) << "Notifying finished size:" << i->size().width() << "," << i->size().height();
#endif
        c->updatePixmap( QRect(QPoint(0, 0), pixmap_size()), this );
        c->notifyFinished( this );
    }
}
