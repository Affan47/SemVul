handleKRB4Level(Connection *conn, value option)
{
    CAMLparam1(option);
    CURLcode result = CURLE_OK;

    switch (Long_val(option))
    {
    case 0:
        result = curl_easy_setopt(conn->connection,
                                  CURLOPT_KRB4LEVEL,
                                  NULL);
        break;

    case 1:
        result = curl_easy_setopt(conn->connection,
                                  CURLOPT_KRB4LEVEL,
                                  "clear");
        break;

    case 2:
        result = curl_easy_setopt(conn->connection,
                                  CURLOPT_KRB4LEVEL,
                                  "safe");
        break;

    case 3:
        result = curl_easy_setopt(conn->connection,
                                  CURLOPT_KRB4LEVEL,
                                  "confidential");
        break;

    case 4:
        result = curl_easy_setopt(conn->connection,
                                  CURLOPT_KRB4LEVEL,
                                  "private");
        break;

    default:
        failwith("Invalid KRB4 Option");
        break;
    }

    if (result != CURLE_OK)
        raiseError(conn, result);

    CAMLreturn0;
}
