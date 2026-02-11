fetchRequestRedirected( QNetworkReply *oldReply,
                                      QNetworkReply *newReply )
{
    KUrl oldUrl = oldReply->request().url();
    KUrl newUrl = newReply->request().url();


    if( m_urls.contains( oldUrl ) && !m_urls.contains( newUrl ) )
    {

        CoverFetchUnit::Ptr unit = m_urls.value( oldUrl );


        m_urls.insert( newUrl, unit );
        m_urls.remove( oldUrl );


        if( unit->isInteractive() )
            Amarok::Components::logger()->newProgressOperation( newReply, i18n( "Fetching Cover" ) );
    }
}
