useGlobalKeyBindings()
{
    if ( d->m_delegate ) {
        d->m_delegate->useGlobalKeyBindings();
        return;
    }

    d->m_keyMap.clear();
    d->m_keyMap.insert( TextCompletion, KShortcut() );
    d->m_keyMap.insert( PrevCompletionMatch, KShortcut() );
    d->m_keyMap.insert( NextCompletionMatch, KShortcut() );
    d->m_keyMap.insert( SubstringCompletion, KShortcut() );
}
