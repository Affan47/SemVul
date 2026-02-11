write_data (Session *session, const void *buf, size_t count)
{
    if (write (session->priv->to_child_input, buf, count) != count)
        l_warning (session, "Error writing to session: %s", strerror (errno));
}
