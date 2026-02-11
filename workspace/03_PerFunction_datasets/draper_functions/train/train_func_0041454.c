slotRestoreData(const QByteArray &data )
{

  if ( !d->m_workingURL.isEmpty() )
  {
     long saveCacheId = d->m_cacheId;
     QString savePageReferrer = d->m_pageReferrer;
     QString saveEncoding     = d->m_encoding;
     begin( d->m_workingURL, arguments().xOffset(), arguments().yOffset() );
     d->m_encoding     = saveEncoding;
     d->m_pageReferrer = savePageReferrer;
     d->m_cacheId = saveCacheId;
     d->m_workingURL = KUrl();
  }


  write( data.data(), data.size() );

  if (data.size() == 0)
  {


    if (d->m_doc && d->m_doc->parsing())
        end();
  }
}
