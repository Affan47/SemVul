initializeLoggerList(LoggerList& list) const
{
    for(LoggerMap::const_iterator it=loggerPtrs.begin();
        it!= loggerPtrs.end();
        ++it)
    {
        list.push_back((*it).second);
    }
}
