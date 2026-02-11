get_config_entry(char * in_data, const char *section, const char *key)
{
    char *ptr = NULL, *p, *tmp;
    char *line;
    int in_section = 0;
    char * data = strdup(in_data);

    for (line = strtok_r(data, "\n", &ptr); line != NULL;
         line = strtok_r(NULL, "\n", &ptr)) {

        while (isspace((unsigned char)*line) && (*line != '\0'))
            line++;


        if (*line == '#') {
            continue;
        }


        if (*line == '[') {
            line++;
            p = strchr(line, ']');
            if (p) {
                tmp = strndup(line, p - line);
                if (in_section) {

                    free(data);
                    return NULL;
                }
                if (strcmp(section, tmp) == 0) {
                    free(tmp);
                    in_section = 1;
                    continue;
                }
            }
        }

        p = strchr(line, '=');
        if (p != NULL && in_section) {

            while (p != line && isspace((unsigned char)p[-1]))
                p--;


            tmp = strndup(line, p - line);
            if (strcmp(key, tmp) != 0) {
                free(tmp);
            } else {
                free(tmp);


                line = strchr(line, '=');
                line++;
                while (isspace((unsigned char)*line) && (*line != '\0'))
                    line++;


                p = strchr(line, '\0');
                while (p != line && isspace((unsigned char)p[-1]))
                    p--;


                tmp = strndup(line, p - line);

                free(data);
                return tmp;
            }
        }
    }
    free(data);
    return NULL;
}
