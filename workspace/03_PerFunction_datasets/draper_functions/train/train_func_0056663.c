send_ftp_err(struct ftp_r *ftp_r)
{
char	*err_header =
"HTTP/1.0 400 Got error during ftp load\r\nContent-Type: text/html\r\n\r\n<html><header>FTP error</header><body><center>Document can't be retrieved.</center><br>Server answers:<hr><p><pre>";
char	*epilog = "</body></html>";

    writet(ftp_r->client, err_header, strlen(err_header), READ_ANSW_TIMEOUT);
    ftp_r->server_log?writet(ftp_r->client,
    		ftp_r->server_log->data, ftp_r->server_log->used, READ_ANSW_TIMEOUT):
    	writet(ftp_r->client, "Undefined error\n", strlen("Undefined error\n"), READ_ANSW_TIMEOUT);
    writet(ftp_r->client, epilog, strlen(epilog), READ_ANSW_TIMEOUT);
}
