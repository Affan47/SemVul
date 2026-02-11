VerifyArrayLength(ParamArray *arr, int required,
    const char *command) {
    if (arr->nelems != required) {
        Error("\"%s\" requires a %d element array! (%d found)",
                    command, required, arr->nelems);
        return false;
    }
    return true;
}
