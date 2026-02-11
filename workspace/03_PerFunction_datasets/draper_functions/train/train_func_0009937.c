fields_file_read(void *source, const char **buffer, size_t *buffer_size)
{
    struct fields_file *self = source;
    size_t size;

    size = fread(self->buffer, 1, self->buffer_size, self->file);
    if (size != self->buffer_size) {
        if (ferror(self->file))
            return FIELDS_FAILURE;
    }

    *buffer = self->buffer;
    *buffer_size = size;

    return 0;
}
