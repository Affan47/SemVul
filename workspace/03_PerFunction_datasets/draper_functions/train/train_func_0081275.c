_duo_prompt(struct duo_ctx *ctx, bson *obj, int flags, char *buf,
    size_t sz, const char **p)
{
    bson_iterator it;
    char *pos, *passcode;

    passcode = getenv(DUO_ENV_VAR_NAME);

    if ((flags & DUO_FLAG_ENV) && (passcode != NULL)) {
        *p = passcode;
        ctx->conv_status(NULL, ENV_VAR_MSG);
    } else if ((flags & DUO_FLAG_AUTO) != 0) {

        _BSON_FIND(ctx, &it, obj, "factors", bson_object);
        bson_iterator_subobject(&it, obj);

        if (bson_find(&it, obj, "default") != bson_string) {
            _duo_seterr(ctx, "No default factor found for automatic login");
            return (DUO_ABORT);
        }
        *p = bson_iterator_string(&it);
        if (ctx->conv_status) {
            if ((pos = strstr(*p, "push"))) {
                ctx->conv_status(NULL, AUTOPUSH_MSG);
            } else if ((pos = strstr(*p, "phone"))) {
                ctx->conv_status(NULL, AUTOPHONE_MSG);
            } else {
                ctx->conv_status(NULL, AUTODEFAULT_MSG);
            }
        }
    } else {

        if (ctx->conv_prompt == NULL) {
            _duo_seterr(ctx, "No prompt function set");
            return (DUO_CLIENT_ERROR);
        }
        _BSON_FIND(ctx, &it, obj, "prompt", bson_string);
        *p = bson_iterator_string(&it);

        if (ctx->conv_prompt(ctx->conv_arg, *p, buf, sz) == NULL) {
            _duo_seterr(ctx, "Error gathering user response");
            return (DUO_ABORT);
        }
        strtok(buf, "\r\n");

        _BSON_FIND(ctx, &it, obj, "factors", bson_object);
        bson_iterator_subobject(&it, obj);

        if (bson_find(&it, obj, buf) == bson_string) {
            *p = bson_iterator_string(&it);
        } else {
            *p = buf;
        }
    }
    return (DUO_CONTINUE);
}
