xmlcontent2plaintext(const char *content)
{
    const char *lookahead, *amp;
    char c, *translated, *cur;

    rum_set_error(NULL);


    if (content == NULL) {
        return "";
    }


    if ((translated = malloc(strlen(content) + 1)) == NULL) {
        rum_set_error("Unable to allocate memory for parsed text");
        return NULL;
    }


    lookahead = content;
    amp = NULL;
    cur = translated;
    while (*lookahead) {
        c = *lookahead;
        switch (c) {

            case '<':
                free(translated);
                rum_set_error("'<' not allowed here");
                return NULL;


            case '&':
                if (amp) {
                    free(translated);
                    rum_set_error("'&' not allowed here");
                    return NULL;
                }
                amp = lookahead;
                break;


            case ';':
                if (amp) {

                    if (!strncmp(amp, "&lt;", (lookahead - amp))) {
                        c = '<';
                    } else if (!strncmp(amp, "&gt;", (lookahead - amp))) {
                        c = '>';
                    } else if (!strncmp(amp, "&amp;", (lookahead - amp))) {
                        c = '&';
                    } else if (!strncmp(amp, "&apos;", (lookahead - amp))) {
                        c = '\'';
                    } else if (!strncmp(amp, "&quot;", (lookahead - amp))) {
                        c = '\"';
                    } else {
                        free(translated);
                        rum_set_error("Unknown entity");
                        return NULL;
                    }
                    amp = NULL;
                }
                break;
        }
        if (!amp) {
            *cur++ = c;
        }
        ++lookahead;
    }
    *cur = 0;


    if (amp) {
        free(translated);
        rum_set_error("'&' not allowed here");
        return NULL;
    }

    return translated;
}
