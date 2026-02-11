utf16_encode(textio *self, PyObject *text)
{
    if (!self->encoding_start_of_stream) {

#if defined(WORDS_BIGENDIAN)
        return utf16be_encode(self, text);
#else
        return utf16le_encode(self, text);
#endif
    }
    return PyUnicode_EncodeUTF16(PyUnicode_AS_UNICODE(text),
                                 PyUnicode_GET_SIZE(text),
                                 PyBytes_AS_STRING(self->errors), 0);
}
