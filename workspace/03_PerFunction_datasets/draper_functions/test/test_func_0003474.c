makeCompletion( const QString& text )
{
    KCompletion *comp = compObj();
    KGlobalSettings::Completion mode = completionMode();

    if ( !comp || mode == KGlobalSettings::CompletionNone )
        return;

    const QString match = comp->makeCompletion( text );

    if ( mode == KGlobalSettings::CompletionPopup ||
         mode == KGlobalSettings::CompletionPopupAuto )
    {
        if ( match.isEmpty() )
        {
            if ( d->completionBox )
            {
                d->completionBox->hide();
                d->completionBox->clear();
            }
        }
        else
            setCompletedItems( comp->allMatches() );
    }
    else
    {


        if ( match.isEmpty() || match == text )
            return;

        if ( mode != KGlobalSettings::CompletionShell )
            setUserSelection(false);

        if ( d->autoSuggest )
            setCompletedText( match );
    }
}
