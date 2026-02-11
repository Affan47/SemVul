WriteLog(const char* pch, const char* LogFile)
{
    FILE* f;
    time_t ltime;
    char szTime[40];
    char* p;
    int rc;
    static pthread_mutex_t* pmtxLog;
    static bool logInit = false;

    char* cp = strdup(pch);

    if (!logInit) {
        pmtxLog = new pthread_mutex_t;
        pthread_mutex_init(pmtxLog,NULL);
        logInit = true;
    }

    pthread_mutex_lock(pmtxLog);

    char* pLogFile = new char[CONFPATH.length() + strlen(LogFile) +1];
    strcpy(pLogFile,CONFPATH.c_str());
    strcat(pLogFile, LogFile);

    f = fopen(pLogFile, "a");

    if (f == NULL)
        f = fopen(pLogFile, "w");

    if (f == NULL) {
        cerr << "failed to open " << pLogFile << endl;
        rc = -1;
    } else {
        char *eol = strpbrk(cp,"\n\r");
        if (eol)
            *eol = '\0';

        time(&ltime) ;
        ctime_r(&ltime,szTime);

        p = strchr(szTime, (int)'\n');

        if (p)
            *p = ' ';

        fprintf(f,"%s %s\n", szTime, cp);
        fflush(f);
        fclose(f);
        rc = 0;
    }
    delete cp;
    delete pLogFile;
    pthread_mutex_unlock(pmtxLog);

    return rc;
}
