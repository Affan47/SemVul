strip_crlf(char *line)
{
    avsize_t len = strlen(line);

    if(len > 0 && line[len-1] == '\n') {
        if(len > 1 && line[len-2] == '\r')
            line[len-2] = '\0';
        else
            line[len-1] = '\0';
    }
}
