processInlineBuffer(redisClient *c) {
    char *newline = strstr(c->querybuf,"\r\n");
    int argc, j;
    sds *argv;
    size_t querylen;


    if (newline == NULL) {
        if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
            addReplyError(c,"Protocol error: too big inline request");
            setProtocolError(c,0);
        }
        return REDIS_ERR;
    }


    querylen = newline-(c->querybuf);
    argv = sdssplitlen(c->querybuf,querylen," ",1,&argc);


    c->querybuf = sdsrange(c->querybuf,querylen+2,-1);


    if (c->argv) zfree(c->argv);
    c->argv = zmalloc(sizeof(robj*)*argc);


    for (c->argc = 0, j = 0; j < argc; j++) {
        if (sdslen(argv[j])) {
            c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
            c->argc++;
        } else {
            sdsfree(argv[j]);
        }
    }
    zfree(argv);
    return REDIS_OK;
}
