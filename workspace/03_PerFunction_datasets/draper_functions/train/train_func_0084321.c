http_process_status_line(struct httplocalfile *lf, char *line)
{
    const char *s;
    int statuscode;
    int res;

    for(s = line; *s && *s != ' '; s++);

    if(s[0] != ' ' ||
       !isdigit((unsigned char) s[1]) ||
       !isdigit((unsigned char) s[2]) ||
       !isdigit((unsigned char) s[3])) {
        av_log(AVLOG_ERROR, "HTTP: bad status code: %s", s);
        return -EIO;
    }

    statuscode = (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');

    av_log(AVLOG_DEBUG, "HTTP: status code: %i", statuscode);

    if(statuscode / 100 == 1) {
        res = http_ignore_header(lf);
        if(res < 0)
            return res;

        return 0;
    }

    if(statuscode / 100 == 2)
        return 1;

    av_log(AVLOG_WARNING, "HTTP: error: %s", s);
    http_ignore_header(lf);

    if(statuscode / 100 == 3 || statuscode / 100 == 4)
        return -ENOENT;

    return -EIO;
}
