_PyUnicode_FormatAdvanced(PyObject *obj,
                          PyObject *format_spec,
                          Py_ssize_t start, Py_ssize_t end)
{
    InternalFormatSpec format;
    PyObject *result;


    if (start == end)
        return PyObject_Str(obj);


    if (!parse_internal_render_format_spec(format_spec, start, end,
                                           &format, 's', '<'))
        return NULL;


    switch (format.type) {
    case 's':

        result = format_string_internal(obj, &format);
        if (result != NULL)
            assert(_PyUnicode_CheckConsistency(result, 1));
        break;
    default:

        unknown_presentation_type(format.type, obj->ob_type->tp_name);
        result = NULL;
    }
    return result;
}
