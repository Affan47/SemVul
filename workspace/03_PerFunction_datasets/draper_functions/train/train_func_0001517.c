jsonsl_jpr_new(const char *path, jsonsl_error_t *errp)
{
    char *my_copy = NULL;
    int count, curidx;
    struct jsonsl_jpr_st *ret = NULL;
    struct jsonsl_jpr_component_st *components = NULL;
    size_t origlen;
    jsonsl_error_t errstacked;

#define JPR_BAIL(err) *errp = err; goto GT_ERROR;

    if (errp == NULL) {
        errp = &errstacked;
    }

    if (path == NULL || *path != '/') {
        JPR_BAIL(JSONSL_ERROR_JPR_NOROOT);
        return NULL;
    }

    count = 1;
    path++;
    {
        const char *c = path;
        for (; *c; c++) {
            if (*c == '/') {
                count++;
                if (*(c+1) == '/') {
                    JPR_BAIL(JSONSL_ERROR_JPR_DUPSLASH);
                }
            }
        }
    }
    if(*path) {
        count++;
    }

    components = (struct jsonsl_jpr_component_st *)
            malloc(sizeof(*components) * count);
    if (!components) {
        JPR_BAIL(JSONSL_ERROR_ENOMEM);
    }

    my_copy = (char *)malloc(strlen(path) + 1);
    if (!my_copy) {
        JPR_BAIL(JSONSL_ERROR_ENOMEM);
    }

    strcpy(my_copy, path);

    components[0].ptype = JSONSL_PATH_ROOT;

    if (*my_copy) {
        char *cur = my_copy;
        int pathret = JSONSL_PATH_STRING;
        curidx = 1;
        while (pathret > 0 && curidx < count) {
            pathret = populate_component(cur, components + curidx, &cur, errp);
            if (pathret > 0) {
                curidx++;
            } else {
                break;
            }
        }

        if (pathret == JSONSL_PATH_INVALID) {
            JPR_BAIL(JSONSL_ERROR_JPR_BADPATH);
        }
    } else {
        curidx = 1;
    }

    path--;
    origlen = strlen(path) + 1;
    ret = (struct jsonsl_jpr_st *)malloc(sizeof(*ret));
    if (!ret) {
        JPR_BAIL(JSONSL_ERROR_ENOMEM);
    }
    ret->orig = (char *)malloc(origlen);
    if (!ret->orig) {
        JPR_BAIL(JSONSL_ERROR_ENOMEM);
    }
    ret->components = components;
    ret->ncomponents = curidx;
    ret->basestr = my_copy;
    ret->norig = origlen-1;
    strcpy(ret->orig, path);

    return ret;

    GT_ERROR:
    free(my_copy);
    free(components);
    if (ret) {
        free(ret->orig);
    }
    free(ret);
    return NULL;
#undef JPR_BAIL
}
