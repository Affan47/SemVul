slotRedirection(KIO::Job*, const KUrl& url)
{


  emit d->m_extension->setLocationBarUrl( url.prettyUrl() );
  d->m_workingURL = url;
}
