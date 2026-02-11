handleSSHAuthTypes(Connection *conn, value option)
{
#if HAVE_DECL_CURLOPT_SSH_AUTH_TYPES
    CAMLparam1(option);
    CAMLlocal1(listIter);
    CURLcode result = CURLE_OK;
    long authTypes = CURLSSH_AUTH_NONE;

    listIter = option;

    while (!Is_long(listIter))
    {
        switch (Long_val(Field(listIter, 0)))
        {
        case 0:
            authTypes |= CURLSSH_AUTH_ANY;
            break;

        case 1:
            authTypes |= CURLSSH_AUTH_PUBLICKEY;
            break;

        case 2:
            authTypes |= CURLSSH_AUTH_PASSWORD;
            break;

        case 3:
            authTypes |= CURLSSH_AUTH_HOST;
            break;

        case 4:
            authTypes |= CURLSSH_AUTH_KEYBOARD;
            break;

        default:
            failwith("Invalid CURLSSH_AUTH_TYPES Value");
            break;
        }

        listIter = Field(listIter, 1);
    }

    result = curl_easy_setopt(conn->connection,
                              CURLOPT_SSH_AUTH_TYPES,
                              authTypes);

    if (result != CURLE_OK)
        raiseError(conn, result);

    CAMLreturn0;
#else
#warning "libcurl does not implement CURLOPT_SSH_AUTH_TYPES"
    failwith("libcurl does not implement CURLOPT_SSH_AUTH_TYPES");
#endif
}
