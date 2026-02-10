_PyFile_SanitizeMode(char *mode)
{
    char *upos;
    size_t len = strlen(mode);

    if (!len) {
        PyErr_SetString(PyExc_ValueError, "empty mode string");
        return -1;
    }

    upos = strchr(mode, 'U');
    if (upos) {
        memmove(upos, upos+1, len-(upos-mode));

        if (mode[0] == 'w' || mode[0] == 'a') {
            PyErr_Format(PyExc_ValueError, "universal newline "
                         "mode can only be used with modes "
                         "starting with 'r'");
            return -1;
        }

        if (mode[0] != 'r') {
            memmove(mode+1, mode, strlen(mode)+1);
            mode[0] = 'r';
        }

        if (!strchr(mode, 'b')) {
            memmove(mode+2, mode+1, strlen(mode));
            mode[1] = 'b';
        }
    } else if (mode[0] != 'r' && mode[0] != 'w' && mode[0] != 'a') {
        PyErr_Format(PyExc_ValueError, "mode string must begin with "
                    "one of 'r', 'w', 'a' or 'U', not '%.200s'", mode);
        return -1;
    }
#ifdef Py_VERIFY_WINNT

    if (!_PyVerify_Mode_WINNT(mode)) {
        PyErr_Format(PyExc_ValueError, "Invalid mode ('%.50s')", mode);
        return -1;
    }
#endif
    return 0;
}
