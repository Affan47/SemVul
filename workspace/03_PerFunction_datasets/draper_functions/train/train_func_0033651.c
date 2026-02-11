httpLookupStatus(Http *http, int status)
{
    HttpStatusCode  *ep;
    char            *key;

    key = itos(status);
    ep = (HttpStatusCode*) mprLookupKey(http->statusCodes, key);
    if (ep == 0) {
        return "Custom error";
    }
    return ep->msg;
}
