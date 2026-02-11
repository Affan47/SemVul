qof_session_begin (QofSession *session, const char * book_id,
                   gboolean ignore_lock, gboolean create, gboolean force)
{
    gchar *scheme = NULL, *filename = NULL;

    if (!session) return;

    ENTER (" sess=%p ignore_lock=%d, book-id=%s",
           session, ignore_lock,
           book_id ? book_id : "(null)");


    qof_session_clear_error (session);


    if (session->book_id)
    {
        if (ERR_BACKEND_NO_ERR != qof_session_get_error(session))
            qof_session_push_error (session, ERR_BACKEND_LOCKED, NULL);
        LEAVE("push error book is already open ");
        return;
    }


    if (!book_id)
    {
        if (ERR_BACKEND_NO_ERR != qof_session_get_error(session))
            qof_session_push_error (session, ERR_BACKEND_BAD_URL, NULL);
        LEAVE("push error missing book_id");
        return;
    }
    scheme = g_uri_parse_scheme (book_id);
    if (g_strcmp0 (scheme, "file") == 0)
        filename = g_filename_from_uri (book_id, NULL, NULL);
    else if (!scheme)
        filename = g_strdup (book_id);

    if (filename && g_file_test (filename, G_FILE_TEST_IS_DIR))
    {
        if (ERR_BACKEND_NO_ERR == qof_session_get_error(session))
            qof_session_push_error (session, ERR_BACKEND_BAD_URL, NULL);
        g_free (filename);
        g_free (scheme);
        LEAVE("Can't open a directory");
        return;
    }


    qof_session_destroy_backend(session);


    session->book_id = g_strdup (book_id);

    if (filename)
        qof_session_load_backend(session, "file");
    else
        qof_session_load_backend(session, scheme);
    g_free (filename);
    g_free (scheme);


    if (NULL == session->backend)
    {
        g_free(session->book_id);
        session->book_id = NULL;
        if (ERR_BACKEND_NO_ERR == qof_session_get_error(session))
            qof_session_push_error (session, ERR_BACKEND_BAD_URL, NULL);
        LEAVE (" BAD: no backend: sess=%p book-id=%s",
               session,  book_id ? book_id : "(null)");
        return;
    }


    if (session->backend->session_begin)
    {
        char *msg;
        int err;

        (session->backend->session_begin)(session->backend, session,
                                          session->book_id, ignore_lock,
                                          create, force);
        PINFO("Done running session_begin on backend");
        err = qof_backend_get_error(session->backend);
        msg = qof_backend_get_message(session->backend);
        if (err != ERR_BACKEND_NO_ERR)
        {
            g_free(session->book_id);
            session->book_id = NULL;
            qof_session_push_error (session, err, msg);
            LEAVE(" backend error %d %s", err, msg ? msg : "(null)");
            return;
        }
        if (msg != NULL)
        {
            PWARN("%s", msg);
            g_free(msg);
        }
    }

    LEAVE (" sess=%p book-id=%s",
           session,  book_id ? book_id : "(null)");
}
