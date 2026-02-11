setCheckSpellingEnabledInternal( bool check )
{
  emit checkSpellingChanged( check );
  if ( check == d->checkSpellingEnabled )
    return;


  d->checkSpellingEnabled = check;
    if ( check )
    {
        if ( hasFocus() ) {
            createHighlighter();
            if (!spellCheckingLanguage().isEmpty())
                setSpellCheckingLanguage(spellCheckingLanguage());
        }
    }
    else
    {
        delete d->highlighter;
        d->highlighter = 0;
    }
}
