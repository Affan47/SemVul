httpp_parse_response(http_parser_t *parser, const char *http_data, unsigned long len, const char *uri)
{
    char *data;
    char *line[MAX_HEADERS];
    int lines, slen,i, whitespace=0, where=0,code;
    char *version=NULL, *resp_code=NULL, *message=NULL;

    if(http_data == NULL)
        return 0;


    data = (char *)malloc(len+1);
    if (data == NULL) return 0;
    memcpy(data, http_data, len);
    data[len] = 0;

    lines = split_headers(data, len, line);


    slen = strlen(line[0]);
    version = line[0];
    for(i=0; i < slen; i++) {
        if(line[0][i] == ' ') {
            line[0][i] = 0;
            whitespace = 1;
        } else if(whitespace) {
            whitespace = 0;
            where++;
            if(where == 1)
                resp_code = &line[0][i];
            else {
                message = &line[0][i];
                break;
            }
        }
    }

    if(version == NULL || resp_code == NULL || message == NULL) {
        free(data);
        return 0;
    }

    httpp_setvar(parser, HTTPP_VAR_ERROR_CODE, resp_code);
    code = atoi(resp_code);
    if(code < 200 || code >= 300) {
        httpp_setvar(parser, HTTPP_VAR_ERROR_MESSAGE, message);
    }

    httpp_setvar(parser, HTTPP_VAR_URI, uri);
    httpp_setvar(parser, HTTPP_VAR_REQ_TYPE, "NONE");

    parse_headers(parser, line, lines);

    free(data);

    return 1;
}
