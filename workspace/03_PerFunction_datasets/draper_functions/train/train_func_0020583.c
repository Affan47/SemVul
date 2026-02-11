databuf_free(DataBuf *db)
{
    DATABUF_VALIDATE(db);

    if (db->alloc_ptr != NULL) {
        free(db->alloc_ptr);
    }

    db->alloc_ptr  = NULL;
    db->alloc_size = 0;
    db->offset     = 0;
    db->len        = 0;
    db->max_len    = 0;

    DATABUF_VALIDATE(db);
}
