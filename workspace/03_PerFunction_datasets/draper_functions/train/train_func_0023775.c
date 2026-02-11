REMclean(char *buff)
{
    char	*p;

    if ((p = strchr(buff, '\r')) != NULL)
	*p = '\0';
    if ((p = strchr(buff, '\n')) != NULL)
	*p = '\0';


    return buff;
}
