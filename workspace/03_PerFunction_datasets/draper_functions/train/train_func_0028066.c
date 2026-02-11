is_first_kex_packet_follows_guess_wrong(const char *client_kex,
                                                   const char *server_kex) {
    int is_wrong = 1;
    char **server_kex_tokens = NULL;
    char **client_kex_tokens = NULL;

    if ((client_kex == NULL) || (server_kex == NULL)) {
        goto out;
    }

    client_kex_tokens = tokenize(client_kex);

    if (client_kex_tokens == NULL) {
        goto out;
    }

    if (client_kex_tokens[0] == NULL) {
        goto freeout;
    }

    server_kex_tokens = tokenize(server_kex);
    if (server_kex_tokens == NULL) {
        goto freeout;
    }

    is_wrong = (strcmp(client_kex_tokens[0], server_kex_tokens[0]) != 0);

    SAFE_FREE(server_kex_tokens[0]);
    SAFE_FREE(server_kex_tokens);
freeout:
    SAFE_FREE(client_kex_tokens[0]);
    SAFE_FREE(client_kex_tokens);
out:
    return is_wrong;
}
