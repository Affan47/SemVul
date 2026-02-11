xrealloc(char **ptr, int size)
{
    ptr = realloc(ptr, size);
    if (ptr) return ptr;
    perror("realloc()");
    exit(1);
}
