qof_session_get_error (QofSession * session)
{
    QofBackendError err;

    if (!session) return ERR_BACKEND_NO_BACKEND;


    if (ERR_BACKEND_NO_ERR != session->last_err)
    {
        return session->last_err;
    }


    if (! session->backend) return ERR_BACKEND_NO_ERR;

    err = qof_backend_get_error (session->backend);
    session->last_err = err;
    return err;
}
