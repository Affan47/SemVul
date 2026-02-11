mod_config_end(int i)
{
int rc;

    flow_so = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( flow_so >= 0 ) {
        rc = bind(flow_so, (struct sockaddr*)&source, sizeof(source));
        if ( rc != 0 ) {
            printf("netflow:mod_config_end(): bind(): %s\n", strerror(errno));
        }
    }
    return(MOD_CODE_OK);
}
