write_in_buffer(char* buffer, int* where, char* what,
    size_t length, int* buffer_size)
{
    while (*where + length >= *buffer_size){
        *buffer_size = (*buffer_size * 2);
        buffer = realloc(buffer, *buffer_size);
    }
    strncpy(buffer + *where, what, length);
    *where += length;

    return buffer;
}
