slotProgressUpdate()
{
  int percent;
  if ( d->m_loadedObjects < d->m_totalObjectCount )
    percent = d->m_jobPercent / 4 + ( d->m_loadedObjects*300 ) / ( 4*d->m_totalObjectCount );
  else
    percent = d->m_jobPercent;

  if( d->m_bComplete )
    percent = 100;

  if (d->m_statusMessagesEnabled) {
    if( d->m_bComplete )
      emit d->m_extension->infoMessage( i18n( "Page loaded." ));
    else if ( d->m_loadedObjects < d->m_totalObjectCount && percent >= 75 )
      emit d->m_extension->infoMessage( i18np( "%1 Image of %2 loaded.", "%1 Images of %2 loaded.", d->m_loadedObjects, d->m_totalObjectCount) );
  }

  emit d->m_extension->loadingProgress( percent );
}
