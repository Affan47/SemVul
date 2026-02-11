catch_bz2_error(int bzerror)
{
    switch(bzerror) {
        case BZ_OK:
        case BZ_RUN_OK:
        case BZ_FLUSH_OK:
        case BZ_FINISH_OK:
        case BZ_STREAM_END:
            return 0;

#ifdef BZ_CONFIG_ERROR
        case BZ_CONFIG_ERROR:
            PyErr_SetString(PyExc_SystemError,
                            "libbzip2 was not compiled correctly");
            return 1;
#endif
        case BZ_PARAM_ERROR:
            PyErr_SetString(PyExc_ValueError,
                            "Internal error - "
                            "invalid parameters passed to libbzip2");
            return 1;
        case BZ_MEM_ERROR:
            PyErr_NoMemory();
            return 1;
        case BZ_DATA_ERROR:
        case BZ_DATA_ERROR_MAGIC:
            PyErr_SetString(PyExc_IOError, "Invalid data stream");
            return 1;
        case BZ_IO_ERROR:
            PyErr_SetString(PyExc_IOError, "Unknown I/O error");
            return 1;
        case BZ_UNEXPECTED_EOF:
            PyErr_SetString(PyExc_EOFError,
                            "Compressed file ended before the logical "
                            "end-of-stream was detected");
            return 1;
        case BZ_SEQUENCE_ERROR:
            PyErr_SetString(PyExc_RuntimeError,
                            "Internal error - "
                            "Invalid sequence of commands sent to libbzip2");
            return 1;
        default:
            PyErr_Format(PyExc_IOError,
                         "Unrecognized error from libbzip2: %d", bzerror);
            return 1;
    }
}
