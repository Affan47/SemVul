request_add_cookie(struct request *r, char *name, char *value) {
    struct nv *c = r->cookies;

    if (c == NULL) {
        r->cookies = (struct nv *) calloc(sizeof(struct nv), 1);
        c = r->cookies;
    } else {
        while(c->next != NULL) c = c->next;
        c->next = (struct nv *) calloc(sizeof(struct nv), 1);
        c = c->next;
    }

    c->name = (char *) calloc(sizeof(char), strlen(name));
    c->value = (char *) calloc(sizeof(char), strlen(value));
    memcpy(c->name, name, strlen(name));
    memcpy(c->value, value, strlen(value));
}
