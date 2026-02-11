setParentView(K3FileView *parent)
{
    if ( parent ) {
        QObject::connect(sig, SIGNAL( activatedMenu(const KFileItem &,
                                                        const QPoint& ) ),
                parent->sig, SIGNAL( activatedMenu(const KFileItem &,
                                                        const QPoint& )));
        QObject::connect(sig, SIGNAL(dirActivated(KFileItem)),
                parent->sig, SIGNAL(dirActivated(KFileItem)));
        QObject::connect(sig, SIGNAL(fileSelected(KFileItem)),
                parent->sig, SIGNAL(fileSelected(KFileItem)));
        QObject::connect(sig, SIGNAL(fileHighlighted(KFileItem)),
                            parent->sig,SIGNAL(fileHighlighted(KFileItem)));
        QObject::connect(sig, SIGNAL(sortingChanged(QDir::SortFlags)),
                            parent->sig, SIGNAL(sortingChanged(QDir::SortFlags)));
        QObject::connect(sig, SIGNAL(dropped(KFileItem,QDropEvent*,KUrl::List)),
                            parent->sig, SIGNAL(dropped(KFileItem,QDropEvent*,KUrl::List)));
    }
}
