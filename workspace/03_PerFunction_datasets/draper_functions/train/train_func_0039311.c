ftp_check_passv_reply(struct ftpconn *conn, const char *line,
                                 char **resp)
{
    int res;
    int replycode;
    int addrbytes[6];
    char addrbuf[128];
    int port;

    res = ftp_check_reply(conn, line);
    if(res < 0)
        return res;

    replycode = res;

    if(replycode != 227) {
        av_log(AVLOG_ERROR, "FTP: %s", line);
        ftp_close_conn(conn);
        return -EIO;
    }

    av_log(AVLOG_DEBUG, "FTP: %s", line);

    if(line[3] != ' ') {
        av_log(AVLOG_ERROR, "FTP: Multiline reply to PASV: %s", line);
        ftp_close_conn(conn);
        return -EIO;
    }

    res = ftp_get_addrbytes(line, addrbytes);
    if(res < 0) {
        av_log(AVLOG_ERROR, "FTP: Bad reply to PASV: %s", line);
        ftp_close_conn(conn);
        return -EIO;
    }

    port = addrbytes[4] * 0x100 + addrbytes[5];
    sprintf(addrbuf, "%i.%i.%i.%i:%i",
            addrbytes[0], addrbytes[1], addrbytes[2], addrbytes[3], port);

    *resp = av_strdup(addrbuf);

    return 0;
}
