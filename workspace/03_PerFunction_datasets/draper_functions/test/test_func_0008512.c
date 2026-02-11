cmd_logout( ITD_Struct *itd, char *Tag )
{
    char *fn = "cmd_logout";
    char SendBuf[BUFSIZE];
    unsigned int BufLen = BUFSIZE - 1;

    SendBuf[BUFSIZE - 1] = '\0';

    snprintf( SendBuf, BufLen, "* BYE LOGOUT received\r\n%s OK Completed\r\n",
	      Tag );
    if ( IMAP_Write( itd->conn, SendBuf, strlen(SendBuf) ) == -1 )
    {
	syslog(LOG_WARNING, "%s: IMAP_Write() to client failed on sd [%d]: %s", fn, itd->conn->sd, strerror(errno) );
	return( -1 );
    }

    return( 0 );
}
