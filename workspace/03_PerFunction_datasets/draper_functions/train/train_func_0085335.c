CkMalloc(size_t bytes, const char *function, const int line)
{
    void *ret;

    if(NULL == (ret = malloc(bytes * sizeof(char)))) {
        Log(&rLog, LOG_FATAL, "Out of memory (requested from %s:%d)\n", function, line);
    }

    return ret;
}
