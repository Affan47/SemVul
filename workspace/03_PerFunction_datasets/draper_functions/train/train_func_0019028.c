base() const
{
    if ( !impl )
        return 0;

    return static_cast<HTMLCollectionImpl*>( impl )->m_refNode;
}
