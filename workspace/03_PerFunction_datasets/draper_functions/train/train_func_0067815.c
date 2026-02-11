buffer_read_file(struct buffer *buffer, int fd)
{
    struct stat st;
    size_t used = buffer->used + buffer->left;

    if (fstat(fd, &st) < 0)
        return false;
    buffer_resize(buffer, st.st_size + used);
    return buffer_read_all(buffer, fd);
}
