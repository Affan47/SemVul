mock_load (QofBackend *be, QofBook *book, QofBackendLoadType type)
{
    g_assert (be);
    g_assert (book);
    g_assert (be == load_session_struct.be);
    g_assert (book != load_session_struct.oldbook);
    g_assert (qof_book_get_backend (book) == be);
    if (load_session_struct.error)
        qof_backend_set_error (be, ERR_BACKEND_DATA_CORRUPT);
    load_session_struct.load_called = TRUE;
}
