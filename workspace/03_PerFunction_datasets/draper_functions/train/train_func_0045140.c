argument_unavailable_error(char *function_name, char *argument_name) {
    PyErr_Format(PyExc_NotImplementedError,
        "%s%s%s unavailable on this platform",
        (function_name != NULL) ? function_name : "",
        (function_name != NULL) ? ": ": "",
        argument_name);
}
