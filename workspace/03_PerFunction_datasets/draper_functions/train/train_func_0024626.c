showPreview(const KUrl &url)
{
    KMimeType::Ptr mt = KMimeType::findByUrl( url );
    KPreviewWidgetBase *provider = previewProviderFor( mt->name() );
    if ( provider )
    {
        if ( provider != m_stack->currentWidget() )
            clearPreview();

        m_stack->setEnabled( true );
        m_stack->setCurrentWidget( provider );
        provider->showPreview( url );
    }
    else
    {
        clearPreview();
        m_stack->setEnabled( false );
    }
}
