getArcsOut( const PD_URI& s )
{
    POCol ret;
    PD_RDFModelIterator iter = begin();
    PD_RDFModelIterator    e = end();
    for( ; iter != e; ++iter )
    {
        const PD_RDFStatement& st = *iter;
        if( st.getSubject() == s )
        {
            ret.insert( std::make_pair( st.getPredicate(), st.getObject() ));
        }
    }
    return ret;
}
