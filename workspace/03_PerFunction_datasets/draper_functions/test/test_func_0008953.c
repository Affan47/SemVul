httpAddRouteHandler(HttpRoute *route, cchar *name, cchar *extensions)
{
    Http            *http;
    HttpStage       *handler;
    char            *extlist, *word, *tok;

    mprAssert(route);

    http = route->http;
    if ((handler = httpLookupStage(http, name)) == 0) {
        mprError("Can't find stage %s", name);
        return MPR_ERR_CANT_FIND;
    }
    GRADUATE_HASH(route, extensions);

    if (extensions && *extensions) {


        extlist = sclone(extensions);
        word = stok(extlist, " \t\r\n", &tok);
        while (word) {
            if (*word == '*' && word[1] == '.') {
                word += 2;
            } else if (*word == '.') {
                word++;
            } else if (*word == '\"' && word[1] == '\"') {
                word = "";
            }
            mprAddKey(route->extensions, word, handler);
            word = stok(0, " \t\r\n", &tok);
        }

    } else {
        if (mprLookupItem(route->handlers, handler) < 0) {
            GRADUATE_LIST(route, handlers);
            mprAddItem(route->handlers, handler);
        }
        if (handler->match) {
            if (mprLookupItem(route->handlersWithMatch, handler) < 0) {
                GRADUATE_LIST(route, handlersWithMatch);
                mprAddItem(route->handlersWithMatch, handler);
            }
        } else {


            mprAddKey(route->extensions, "", handler);
        }
    }
    return 0;
}
