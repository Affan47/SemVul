readMessage()
{
    int rc;

    if ((rc = rawRead(buf, 7)) > 0 && (buf[6]&128) == 0) {


        while ((buf[6]&128) == 0 && rc > 0) {
            rc = rawRead(&buf[6], 1);
        }


    }
    return rc;
}
