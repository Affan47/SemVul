remctl_validate(struct webauth_context *ctx, const char *user, const char *ip,
                const char *code, const char *type, const char *state,
                struct webauth_user_validate **validate)
{
    int s;
    const char *argv[8];
    apr_xml_doc *doc;
    struct webauth_user_config *c = ctx->user;

    argv[0] = c->command;
    argv[1] = "webkdc-validate";
    argv[2] = user;
    argv[3] = ip;
    argv[4] = code;
    argv[5] = type;
    argv[6] = state;
    argv[7] = NULL;
    s = remctl_generic(ctx, argv, &doc);
    if (s != WA_ERR_NONE)
        return s;
    return parse_user_validate(ctx, doc, validate);
}
