sf_string_destroy_index(void *p)
{
    StringIndex *self = (StringIndex *)p;
    int i;
    free(self->index);
    for (i = 0; i < self->v_size; i++) {
        free(self->values[i]);
    }
    free(self->values);
    free(self);
}
