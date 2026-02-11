setPattern( const QString& pattern )
{
    if ( d->options & KFind::FindIncremental && d->pattern != pattern )
        d->patternChanged = true;

    d->pattern = pattern;
    setOptions( options() );
}
