fields_reader_fill(struct fields_reader *self)
{
    int result;

    result = self->source_read(self->source, &self->buffer, &self->buffer_size);
    self->cursor = self->buffer;

    if (result != 0) {
        self->error = FIELDS_READER_ERROR_UNREADABLE_SOURCE;
        return FIELDS_FAILURE;
    }

    return 0;
}
