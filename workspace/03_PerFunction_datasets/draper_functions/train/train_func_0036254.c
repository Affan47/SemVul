get_cpu_page_data_24(struct os_statistics *stats) {

    int res = 0;
    FILE *f = NULL;

    char buf[4096];
    char *strptr = NULL;
    unsigned long long user = 0;
    unsigned long long userlow = 0;
    unsigned long long sys = 0;
    unsigned long long idle = 0;
    unsigned long long pages_in = 0;
    unsigned long long pages_out = 0;

    _OSBASE_TRACE(3,("get_cpu_page_data_24() called"));

    int read_count = 0;
    if ((f = fopen(DATA_FILE,"r")) != NULL) {
        read_count = fread(buf,sizeof(char),sizeof(buf)-1,f);
        buf[read_count] = '\0';
        fclose(f);


        if (sscanf(buf,"cpu %lld %lld %lld %lld",&user,&userlow,&sys, &idle) == 4) {
            stats->user_time = (user + userlow) * 10;
            stats->system_time = sys * 10;
            stats->idle_time = idle * 10;
            stats->wait_time = 0;
            strptr = strstr(buf,"page");


            if (sscanf(strptr,"page %lld %lld",&pages_in, &pages_out) == 2) {
                stats->pages_in = pages_in;
                stats->pages_out = pages_out;
                res = 1;
            } else {
                _OSBASE_TRACE(1,("get_cpu_page_data_24(): could not find page in/out data"));
            }
        } else {
            _OSBASE_TRACE(1,("get_cpu_page_data_24(): could not find cpu data"));
        }
    } else {
        _OSBASE_TRACE(1,("get_cpu_page_data_24():could not open %s: %s",DATA_FILE,strerror(errno)));
    }
    _OSBASE_TRACE(4,("get_cpu_page_data_24() res. %d",res));
    _OSBASE_TRACE(3,("get_cpu_page_data_24() exited"));
    return res;
}
