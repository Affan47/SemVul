fat_datetime(time_t time,int return_time) {
    struct tm* t;
#ifdef _WIN32
    t=localtime(&time);
#else
    struct tm t1;
    t=&t1;
    localtime_r(&time,t);
#endif
    if(return_time)
	return cpu_to_le16((t->tm_sec/2)|(t->tm_min<<5)|(t->tm_hour<<11));
    return cpu_to_le16((t->tm_mday)|((t->tm_mon+1)<<5)|((t->tm_year-80)<<9));
}
