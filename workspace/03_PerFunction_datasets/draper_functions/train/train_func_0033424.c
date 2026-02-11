getAllNames() const
{
    OFList<log4cplus::tstring> tmp;
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        for(ObjectMap::const_iterator it=data.begin(); it!=data.end(); ++it)
            tmp.push_back( (*it).first );
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
    return tmp;
}
