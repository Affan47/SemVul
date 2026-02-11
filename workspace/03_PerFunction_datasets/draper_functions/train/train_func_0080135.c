parse_client_request(char *header_line) {
        char *method, *request_uri, *http_version;

#ifdef DEBUG
        ASSERT(header_line);
        ASSERT(strlen(header_line) > 0);
#endif

        method = header_line;

        if ((request_uri = strchr(method, ' ')) == NULL) return 1;
        *request_uri++ = '\0';
        while (isspace(*request_uri)) request_uri++;

        if ((http_version = strchr(request_uri, ' ')) == NULL) return 1;
        *http_version++ = '\0';
        while (isspace(*http_version)) http_version++;

        if (strncmp(http_version, HTTP_STRING, strlen(HTTP_STRING)) != 0) return 1;

        insert_value("method", method);
        insert_value("request-uri", request_uri);
        insert_value("http-version", http_version);
        insert_value("direction", ">");

        return 0;
}
