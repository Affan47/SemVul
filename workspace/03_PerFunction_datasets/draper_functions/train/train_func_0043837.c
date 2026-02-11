aisc_client_get_hostname(void){
    static char *hn = 0;
    if (!hn){
        char buffer[4096];
        gethostname(buffer,4095);
        hn = strdup(buffer);
    }
    return hn;
}
