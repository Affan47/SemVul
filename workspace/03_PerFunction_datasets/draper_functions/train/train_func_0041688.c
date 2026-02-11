get_line(ByteIOContext *s, char *buf, int maxlen)
{
    int i = 0;
    char c;

    do{
        c = get_byte(s);
        if (i < maxlen-1)
            buf[i++] = c;
    }while(c != '\n' && c);

    buf[i] = 0;
}
