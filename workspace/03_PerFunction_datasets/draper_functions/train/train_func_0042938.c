includeLabelsFrom()
{
    QAction *action = qobject_cast<QAction *>( sender() );
    if( !action )
    {
        warning() << __PRETTY_FUNCTION__ << "must only be called from QAction";
        return;
    }

    ProviderPtr provider = action->data().value<ProviderPtr>();
    if( provider )
        m_matchedTracksModel->includeLabelsFrom( provider );
}
