startDrag(Qt::DropActions supportedActions)
{
    DEBUG_BLOCK


    if( !( QApplication::mouseButtons() & Qt::LeftButton ) )
        return;

    QModelIndexList indices = selectedIndexes();
    if( indices.isEmpty() )
        return;


    if( m_ongoingDrag )
        return;
    m_ongoingDrag = true;

    if( !m_pd )
        m_pd = The::popupDropperFactory()->createPopupDropper( Context::ContextView::self() );

    if( m_pd && m_pd->isHidden() )
    {
        if( m_filterModel )
        {
            QModelIndexList tmp;
            foreach( const QModelIndex &idx, indices )
            {
                tmp.append( m_filterModel->mapToSource( idx ) );
            }
            indices = tmp;
        }

        QActionList actions = createBasicActions( indices );

        QFont font;
        font.setPointSize( 16 );
        font.setBold( true );

        foreach( QAction * action, actions )
            m_pd->addItem( The::popupDropperFactory()->createItem( action ) );

        m_currentCopyDestination = getCopyActions( indices );
        m_currentMoveDestination = getMoveActions( indices );

        m_currentItems.clear();
        foreach( const QModelIndex &index, indices )
        {
            if( index.isValid() && index.internalPointer() )
            {
                m_currentItems.insert(
                        static_cast<CollectionTreeItem *>( index.internalPointer() ) );
            }
        }

        PopupDropperItem *subItem;

        actions = createExtendedActions( indices );

        PopupDropper *morePud = 0;
        if( actions.count() > 1 )
        {
            morePud = The::popupDropperFactory()->createPopupDropper( 0, true );

            foreach( QAction *action, actions )
                morePud->addItem( The::popupDropperFactory()->createItem( action ) );
        }
        else
            m_pd->addItem( The::popupDropperFactory()->createItem( actions[0] ) );


        if ( actions.count() > 1 )
        {
            subItem = m_pd->addSubmenu( &morePud, i18n( "More..." )  );
            The::popupDropperFactory()->adjustItem( subItem );
        }

        m_pd->show();
    }

    QTreeView::startDrag( supportedActions );
    debug() << "After the drag!";

    if( m_pd )
    {
        debug() << "clearing PUD";
        connect( m_pd, SIGNAL(fadeHideFinished()), m_pd, SLOT(clear()) );
        m_pd->hide();
    }

    m_ongoingDrag = false;
}
