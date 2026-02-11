rhk_sm4_read_page_data(RHKPage *page,
                       const RHKObject *obj,
                       const guchar *buffer,
                       GError **error)
{
    gsize expected_size;

    expected_size = 4 * page->x_size * page->y_size;
    if (err_SIZE_MISMATCH(error, expected_size, obj->size, TRUE))
        return FALSE;

    page->data = buffer + obj->offset;

    return TRUE;
}
