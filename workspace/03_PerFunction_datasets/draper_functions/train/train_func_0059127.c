home()
{
    DEBUG_BLOCK
    if( activeCategory() )
    {
        BrowserCategoryList *childList = qobject_cast<BrowserCategoryList*>( activeCategory() );
        if( childList )
            childList->home();

        activeCategory()->clearAdditionalItems();
        m_widgetStack->setCurrentIndex( 0 );

        emit( viewChanged() );
    }
}
