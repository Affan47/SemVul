scrub_cb (const char *type, gpointer data_p, gpointer be_data_p)
{
    GncXmlDataType_t *data = data_p;
    struct file_backend *be_data = be_data_p;

    g_return_if_fail (type && data && be_data);
    g_return_if_fail (data->version == GNC_FILE_BACKEND_VERS);

    if (data->scrub)
        (data->scrub)(be_data->book);
}
