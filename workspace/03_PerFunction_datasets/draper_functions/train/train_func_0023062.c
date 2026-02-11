flush_character_buffer(xmlparseobject *self)
{
    int rc;
    if (self->buffer == NULL || self->buffer_used == 0)
        return 0;
    rc = call_character_handler(self, self->buffer, self->buffer_used);
    self->buffer_used = 0;
    return rc;
}
