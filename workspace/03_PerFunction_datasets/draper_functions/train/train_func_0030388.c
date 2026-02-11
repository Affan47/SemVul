tidy_smtp_mess(char *error, char *printstring, char *outbuf, size_t outbuflen)
{
    while(isdigit((unsigned char)*error) || isspace((unsigned char)*error) ||
	  (*error == '.' && isdigit((unsigned char)*(error+1))))
      error++;

    snprintf(outbuf, outbuflen, printstring, error);
    outbuf[outbuflen-1] = '\0';
    return(outbuf);
}
