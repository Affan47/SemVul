PyMarshal_ReadLastObjectFromFile(FILE *fp)
{

#define REASONABLE_FILE_LIMIT (1L << 18)
#ifdef HAVE_FSTAT
    off_t filesize;
    filesize = getfilesize(fp);
    if (filesize > 0 && filesize <= REASONABLE_FILE_LIMIT) {
        char* pBuf = (char *)PyMem_MALLOC(filesize);
        if (pBuf != NULL) {
            size_t n = fread(pBuf, 1, (size_t)filesize, fp);
            PyObject* v = PyMarshal_ReadObjectFromString(pBuf, n);
            PyMem_FREE(pBuf);
            return v;
        }

    }
#endif


    return PyMarshal_ReadObjectFromFile(fp);

#undef REASONABLE_FILE_LIMIT
}
