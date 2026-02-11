qt_close(void *handle)
{
    struct qt_handle *h = handle;

    quicktime_close(h->qt);
    if (h->rows)
	free(h->rows);
    free(h);
    return 0;
}
