log_message(PyObject *self, PyObject *args) {
    LogLevel level;
    int intLevel;
    char *message;

    if (!PyArg_ParseTuple(args, "is", &intLevel, &message))
        return NULL;

    switch (intLevel) {
    case llevError:
        level = llevError;
        break;

    case llevInfo:
        level = llevInfo;
        break;

    case llevDebug:
        level = llevDebug;
        break;

    case llevMonster:
        level = llevMonster;
        break;

    default:
        return NULL;
    }
    if ((message != NULL) && (message[strlen(message)] == '\n'))
        cf_log(level, "CFPython: %s", message);
    else
        cf_log(level, "CFPython: %s\n", message);
    Py_INCREF(Py_None);
    return Py_None;
}
