filter() const
{
    return QUrl::toPercentEncoding( m_filterProxy->filterRegExp().pattern() );
}
