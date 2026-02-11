init(const KUrl::List &urls)
{
    KUrl::List::ConstIterator uit = urls.begin();
    KUrl::List::ConstIterator uEnd = urls.end();


    for ( ; uit != uEnd ; ++uit )
    {
        m_urls.append( urlToString(*uit).toLatin1().constData() );
    }
    setUris(m_urls);
}
