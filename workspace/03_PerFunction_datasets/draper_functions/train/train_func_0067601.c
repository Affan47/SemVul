skipEol(const char *restrict buf, int i)
{
    while(buf[i] == ' ')
        i++;
    if(buf[i] == '\n')
        return i + 1;
    else if(buf[i] == '\r') {
        if(buf[i + 1] == '\n')
            return i + 2;
        else
            return -1;
    } else {
        return -1;
    }
}
