MakeToken(char *ng, unsigned long artnum, STORAGECLASS class) {
    TOKEN token;
    NGTENT *ngtp;
    unsigned long num;

    memset(&token, '\0', sizeof(token));

    token.type = TOKEN_TRADSPOOL;
    token.class = class;


    if ((ngtp = FindNGByName(ng)) == NULL) {
        AddNG(ng, 0);
        DumpDB();
        ngtp = FindNGByName(ng);
    }

    num = ngtp->ngnumber;
    num = htonl(num);

    memcpy(token.token, &num, sizeof(num));
    artnum = htonl(artnum);
    memcpy(&token.token[sizeof(num)], &artnum, sizeof(artnum));
    return token;
}
