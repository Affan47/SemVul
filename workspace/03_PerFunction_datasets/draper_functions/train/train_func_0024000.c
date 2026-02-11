_storage_filter(pool_t p, const char *f, int len) {
    char *c, *key, *val, *sub;
    int vallen;
    st_filter_t res, sf;

    if(f[0] != '(' && f[len] != ')')
        return NULL;


    if(isalpha(f[1])) {
        key = strdup(f+1);

        c = strchr(key, '=');
        if(c == NULL) {
		free(key);
		return NULL;
	}
        *c = '\0'; c++;

        val = c;


        while (*c != ':' && *c != ')' && *c)
           c++;

        if (!*c) {
		free(key);
		return NULL;
	}

        if (*c == ':') {

                *c = '\0';
                vallen = atoi(val);
                c++;
                val = c;
                c += vallen;
        }

        *c = '\0';
        log_debug(ZONE, "extracted key %s val %s", key, val);

        res = pmalloco(p, sizeof(struct st_filter_st));
        res->p = p;

        res->type = st_filter_type_PAIR;
        res->key = pstrdup(p, key);
        res->val = pstrdup(p, val);

	free(key);
        return res;
    }


    if(f[1] != '&' && f[1] != '|' && f[1] != '!')
        return NULL;

    res = pmalloco(p, sizeof(struct st_filter_st));
    res->p = p;

    switch(f[1]) {
        case '&': res->type = st_filter_type_AND; break;
        case '|': res->type = st_filter_type_OR; break;
        case '!': res->type = st_filter_type_NOT; break;
    }


    c = (char *) &f[2];
    while(*c == '(') {
        sub = c;
        c = strchr(sub, ')');
        c++;

        sf = _storage_filter(p, (const char *) sub, c - sub);

        sf->next = res->sub;
        res->sub = sf;
    }

    return res;
}
