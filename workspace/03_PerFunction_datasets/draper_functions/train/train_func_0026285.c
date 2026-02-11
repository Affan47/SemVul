ConfigurationWatchDogThread(const tstring& file, unsigned int millis)
        : PropertyConfigurator(file)
        , waitMillis(waitMillis < 1000 ? 1000 : millis)
        , shouldTerminate(false)
        , lock(NULL)
    { }
