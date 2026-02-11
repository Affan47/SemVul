emitSelectionChanged()
{


    if (!d->m_activeFrame)
    {
        emit d->m_extension->enableAction( "copy", hasSelection() );
        emit d->m_extension->selectionInfo( selectedText() );
        emit selectionChanged();
    }
}
