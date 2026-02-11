get_host_username(UDR_Options * udr_options, int argc, char *argv[], int rsync_arg_idx){
    bool src_remote = true;
    bool dest_remote = true;


    char dest_username[PATH_MAX+1];
    char dest_host[PATH_MAX+1];
    bool dest_double_colon = false;
    dest_username[0] = '\0';
    dest_host[0] = '\0';

    char next_src_username[PATH_MAX+1];
    char next_src_host[PATH_MAX+1];
    bool next_src_double_colon = false;
    next_src_username[0] = '\0';
    next_src_host[0] = '\0';

    char src_username[PATH_MAX+1];
    char src_host[PATH_MAX+1];
    bool src_double_colon = false;
    src_username[0] = '\0';
    src_host[0] = '\0';

    int src_username_len, src_host_len, dest_username_len, dest_host_len;

    char * dest = argv[argc-1];


    int src_num = 0;
    for(int i = argc-2; i > rsync_arg_idx; i--){

        if(argv[i][0] == '-'){
            break;
        }
        else{


            parse_host_username(argv[i], next_src_username, next_src_host, &next_src_double_colon);


            if(src_num != 0){
                if(strcmp(src_username,next_src_username) != 0 || strcmp(src_host,next_src_host) != 0 || src_double_colon != next_src_double_colon){

                    fprintf(stderr, "UDR ERROR: source must use the same host and username\n");
                    exit(-1);
                }
            }
            snprintf(src_username, PATH_MAX, "%s", next_src_username);
            snprintf(src_host, PATH_MAX, "%s", next_src_host);
            src_double_colon = next_src_double_colon;
            next_src_username[0] = '\0';
            next_src_host[0] = '\0';
            next_src_double_colon = false;
            src_num++;
        }
    }


    if(strlen(src_host) == 0){
        src_remote = false;
    }


    parse_host_username(dest, dest_username, dest_host, &dest_double_colon);


    if(strlen(dest_host) == 0){
        dest_remote = false;
    }


    if(src_remote == dest_remote){
        fprintf(stderr, "UDR ERROR: UDR only does remote -> local or local -> remote transfers\n");
        exit(-1);
    }

    if(src_remote){
        snprintf(udr_options->host, PATH_MAX, "%s", src_host);
        snprintf(udr_options->username, PATH_MAX, "%s", src_username);
        udr_options->server_connect = src_double_colon;
    }
    else{
        snprintf(udr_options->host, PATH_MAX, "%s", dest_host);
        snprintf(udr_options->username, PATH_MAX, "%s", dest_username);
        udr_options->server_connect = dest_double_colon;
    }
}
