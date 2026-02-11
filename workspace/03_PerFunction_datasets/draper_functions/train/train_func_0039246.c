httpGetDateString(MprPath *sbuf)
{
    MprTime     when;

    if (sbuf == 0) {
        when = ((Http*) MPR->httpService)->now;
    } else {
        when = (MprTime) sbuf->mtime * MPR_TICKS_PER_SEC;
    }
    return mprFormatUniversalTime(HTTP_DATE_FORMAT, when);
}
