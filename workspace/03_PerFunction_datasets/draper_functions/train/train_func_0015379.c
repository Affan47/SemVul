xrealloc(void *ptr, size_t size)
{
        void *ret = realloc(ptr, size);
        if (!ret && !size)
                ret = realloc(ptr, 1);
        if (!ret)
                fatal_system_error("Out of memory, realloc failed");
        return ret;
}
