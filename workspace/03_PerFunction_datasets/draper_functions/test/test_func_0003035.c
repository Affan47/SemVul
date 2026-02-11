qof_session_destroy (QofSession *session)
{
    if (!session) return;

    ENTER ("sess=%p book_id=%s", session, session->book_id
           ? session->book_id : "(null)");

    qof_session_end (session);


    qof_session_destroy_backend(session);

    qof_book_set_backend (session->book, NULL);
    qof_book_destroy (session->book);
    session->book  = NULL;

    g_free (session);

    LEAVE ("sess=%p", session);
}
