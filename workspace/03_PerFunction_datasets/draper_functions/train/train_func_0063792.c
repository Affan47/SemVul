config_parse_clause_body(void *config, config_context_t *ctx, config_parse_body_t *parse_body, void *param)
{
    config_token_t tok;

    for (;;) {
        if (config_get_token(&tok, ctx) < 0)
            return 0;

        if (tok.tok_code == CONFIG_TOKEN_BLOCK_CLOSE) {
            config_unget_token(&tok, ctx);
            return 0;
        }

        if (tok.tok_code != CONFIG_TOKEN_STRING) {
            config_error_unexpected(&tok, ctx);
            return -1;
        }

        if (parse_body(config, ctx, &tok, param) < 0)
            return -1;
    }
}
