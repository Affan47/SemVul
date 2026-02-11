lazy_df_destroy(LazyDocField *self)
{
    int i;
    for (i = self->size - 1; i >= 0; i--) {
        if (self->data[i].text) {
            free(self->data[i].text);
         }
    }
    free(self->name);
    free(self->data);
    free(self);
}
