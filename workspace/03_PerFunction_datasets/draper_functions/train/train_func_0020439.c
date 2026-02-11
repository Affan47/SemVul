util_dict_urlencode(util_dict *dict, char delim)
{
    char *res, *tmp;
    char *enc;
    int start = 1;

    for (res = NULL; dict; dict = dict->next) {

        if (!dict->key)
            continue;
        if (start) {
            if (!(res = malloc(strlen(dict->key) + 1))) {
                return NULL;
            }
            sprintf(res, "%s", dict->key);
            start = 0;
        } else {
            if (!(tmp = realloc(res, strlen(res) + strlen(dict->key) + 2))) {
                free(res);
                return NULL;
            } else
                res = tmp;
            sprintf(res + strlen(res), "%c%s", delim, dict->key);
        }


        if (!dict->val)
            continue;
        if (!(enc = util_url_escape(dict->val))) {
            free(res);
            return NULL;
        }

        if (!(tmp = realloc(res, strlen(res) + strlen(enc) + 2))) {
            free(enc);
            free(res);
            return NULL;
        } else
            res = tmp;
        sprintf(res + strlen(res), "=%s", enc);
        free(enc);
    }

    return res;
}
