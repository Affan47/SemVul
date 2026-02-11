set_variable(char *filename, char *name, char *value,
    variable ** var, int *n_vars, int *max_vars)
{


    bool dont_update = false;

    size_t len = strlen(name);

    if (name[len - 1] == '?') {
        dont_update = true;
        len--;
    }
    if (strcmp(name, "pre-up") != 0 && strcmp(name, "up") != 0 && strcmp(name, "down") != 0 && strcmp(name, "post-down") != 0) {
        int j;
        for (j = 0; j < *n_vars; j++) {
            if (strncmpz(name, (*var)[j].name, len) == 0) {
                if (dont_update) {
                    return NULL;
                }

                if ((*var)[j].value == value) {
                    return &(*var)[j];
                }

                free((*var)[j].value);
                (*var)[j].value = strdup(value);
                if (!(*var)[j].value) {
                    perror(filename);
                    return NULL;
                }

                return &((*var)[j]);
            }
        }
    }

    if (*n_vars >= *max_vars) {
        variable *new_var;
        *max_vars += 10;
        new_var = realloc(*var, sizeof(variable) * *max_vars);
        if (new_var == NULL) {
            perror(filename);
            return NULL;
        }
        *var = new_var;
    }

    (*var)[*n_vars].name = strndup(name, len);
    (*var)[*n_vars].value = strdup(value);

    if (!(*var)[*n_vars].name) {
        perror(filename);
        return NULL;
    }

    if (!(*var)[*n_vars].value) {
        perror(filename);
        return NULL;
    }

    (*n_vars)++;
    return &((*var)[(*n_vars) - 1]);
}
