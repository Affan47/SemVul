index_destroy(Index *self)
{
    mutex_destroy(&self->mutex);
    INDEX_CLOSE_READER(self);
    if (self->iw) iw_close(self->iw);
    store_deref(self->store);
    a_deref(self->analyzer);
    if (self->qp) qp_destroy(self->qp);
    if (self->key) hs_destroy(self->key);
    free(self->id_field);
    free(self->def_field);
    free(self);
}
