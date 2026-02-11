addCategory( BrowserCategory *category )
{
    Q_ASSERT( category );

    category->setParentList( this );


    category->setParent( this );
    m_categories[category->name()] = category;
    m_categoryListModel->addCategory( category );
    m_widgetStack->addWidget( category );


    BrowserCategoryList *childList = qobject_cast<BrowserCategoryList*>( category );
    if ( childList )
        connect( childList, SIGNAL(viewChanged()), this, SLOT(childViewChanged()) );

    category->polish();

    if( m_sorting )
    {
        m_proxyModel->sort( 0 );
    }
    emit( viewChanged() );
}
