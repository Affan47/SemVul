qp_destroy(QParser *self)
{
    if (self->close_def_fields) {
        hs_destroy(self->def_fields);
    }
    if (self->tokenized_fields) {
        hs_destroy(self->tokenized_fields);
    }
    if (self->dynbuf) {
        free(self->dynbuf);
    }
    hs_destroy(self->all_fields);
    hs_destroy(self->fields_buf);
    h_destroy(self->field_cache);
    h_destroy(self->ts_cache);
    tk_destroy(self->non_tokenizer);
    a_deref(self->analyzer);
    free(self);
}
