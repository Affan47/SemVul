setPercent( unsigned long percentage )
{
    Q_D(KJob);
    if ( d->percentage!=percentage )
    {
        d->percentage = percentage;
        emit percent( this, percentage );
    }
}
