slotError( int err, const QString & errorText )
{
    Q_D(SimpleJob);
    setError( err );
    setErrorText( errorText );
    if ((error() == ERR_UNKNOWN_HOST) && d->m_url.host().isEmpty())
       setErrorText( QString() );

    slotFinished();
}
