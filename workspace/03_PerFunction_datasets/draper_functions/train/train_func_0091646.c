get_server(char *buff, int buffsize)
{
    char	*p;

    if (fgets(buff, buffsize, ser_rd_fp) == NULL)
	return -1;
    p = &buff[strlen(buff)];
    if (p >= &buff[2] && p[-2] == '\r' && p[-1] == '\n')
	p[-2] = '\0';
    return 0;
}
