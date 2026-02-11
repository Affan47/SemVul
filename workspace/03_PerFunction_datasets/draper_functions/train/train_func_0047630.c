init()
{
    replaceEnvironVariables();
    properties = properties.getPropertySubset( LOG4CPLUS_TEXT("log4cplus.") );
}
