getAllViews() const
{
    UT_GenericVector<AV_View *> t;
    getAllViews( &t );
    std::list<AV_View*> ret;
    for( int i=0; i < t.size(); ++i )
        ret.push_back( (AV_View*)t[i] );
    return ret;
}
