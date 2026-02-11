cli_cmd_tokenize (const char *template)
{
        char **tokens = NULL;
        int    ret = 0;
        int    count = 0;

        ret = is_template_balanced (template);
        if (ret)
                return NULL;

        count = cli_cmd_token_count (template);
        if (count <= 0)
                return NULL;

        tokens = calloc (count + 1, sizeof (char *));
        if (!tokens)
                return NULL;

        ret = cli_cmd_tokens_fill (tokens, template);
        if (ret)
                goto err;

        return tokens;
err:
        cli_cmd_tokens_destroy (tokens);
        return NULL;
}
