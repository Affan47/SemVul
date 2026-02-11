ed_submit_info_event_rm(char *string)
{
    char *p = string;
    int c;
    while ((c=*p)!= 0 ) {
        if (c==':') *p = ';';
        if (c=='=') *p = '-';
        p++;
    }
}
