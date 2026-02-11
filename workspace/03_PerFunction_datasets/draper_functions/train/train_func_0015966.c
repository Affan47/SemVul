find_http_req(const unsigned char *data, const size_t len, unsigned char **http, size_t *httplen) {
    unsigned char *req, *le, *blankline, *hosthdr;

#define remaining(x)    (len - (data - (x)))
#define MAX_REQ         16384


    if (len < 40)
        return (unsigned char*)data;

    if (!(req = memstr(data, len, (unsigned char*) "GET ", 4)))
        return (unsigned char*)(data + len - 4);


    if (!(le = memstr(req + 4, remaining(req + 4), (unsigned char*) "\r\n", 2))) {
        if (remaining(req + 4) > MAX_REQ)
            return (unsigned char*)(req + 4);
        else
            return (unsigned char*)req;
    }


    if (le < req + 5)
        return le + 2;


    if (memcmp(le - 9, " HTTP/1.", 8) || !strchr("01", (int)*(le - 1)))
        return le + 2;


    if (!(blankline = memstr(le + 2, remaining(le + 2), (unsigned char*) "\r\n\r\n", 4))) {
        if (remaining(le + 2) > MAX_REQ)
            return (unsigned char*)(data + len - 4);
        else
            return req;
    }

    if (memcmp(req + 4, "http://", 7) == 0)

        goto found;


    if (!(hosthdr = memstr(le, blankline - le + 2, (unsigned char*) "\r\nHost: ", 8))) {
        return blankline + 4;
    }

found:

    *http = req;
    *httplen = blankline - req;

    return blankline + 4;
}
