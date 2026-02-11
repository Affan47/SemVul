strip_spaces_end(char *buf)
{
    unsigned int i = strlen(buf);

    while(i > 0 && isspace((unsigned char) buf[i-1]))
        i--;
    buf[i] = '\0';
}
