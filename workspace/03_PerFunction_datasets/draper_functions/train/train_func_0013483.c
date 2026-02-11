resetConfiguration()
{
    Logger root = h.getRoot();
    h.disable(log4cplus::Hierarchy::DISABLE_OFF);


    root.setLogLevel(DEBUG_LOG_LEVEL);
    root.closeNestedAppenders();
    root.removeAllAppenders();


    for(LoggerList::iterator it=loggerList.begin(); it!=loggerList.end(); ++it) {
        LOG4CPLUS_MUTEX_UNLOCK( (*it).value->appender_list_mutex ) ;
        (*it).closeNestedAppenders();
        (*it).removeAllAppenders();
        LOG4CPLUS_MUTEX_LOCK( (*it).value->appender_list_mutex ) ;
        (*it).setLogLevel(NOT_SET_LOG_LEVEL);
        (*it).setAdditivity(true);
    }
}
