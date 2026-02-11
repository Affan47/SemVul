decode_icmp_msg(char *line, char *data, struct icmp4_msg_mib *msg)
{
    char *token, *saveptr, *lineptr, *saveptr1, *dataptr, *delim = NULL;
    char line_cpy[1024];
    char data_cpy[1024];
    long index;

    if(data == NULL)
        return -1;


    strlcpy(line_cpy, line, sizeof(line_cpy));
    strlcpy(data_cpy, data, sizeof(data_cpy));

    lineptr = line_cpy;
    dataptr = data_cpy;
    saveptr1 = NULL;
    while (1) {
        if(NULL == (token = strtok_r(lineptr, " ", &saveptr)))
            break;
        lineptr = NULL;
        errno = 0;
        if (0 == strncmp(strsep(&token, "e"), "OutTyp", 6)) {
            index = strtol(token, &delim, 0);
            if (ERANGE == errno) {
                continue;
            } else if (index > LONG_MAX) {
                continue;
            } else if (index < LONG_MIN) {
                continue;
            }
            if (NULL == (token = strtok_r(dataptr, " ", &saveptr1)))
                break;
            dataptr = NULL;
            msg->vals[index].OutType = atoi(token);
        } else {
            index = strtol(token, &delim, 0);
            if (ERANGE == errno) {
                continue;
            } else if (index > LONG_MAX) {
                continue;
            } else if (index < LONG_MIN) {
                continue;
            }
            if(NULL == (token = strtok_r(dataptr, " ", &saveptr1)))
                break;
            dataptr = NULL;
            msg->vals[index].InType = atoi(token);
        }
    }
    return 0;
}
