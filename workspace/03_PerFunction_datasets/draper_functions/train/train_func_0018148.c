hybrid_connection_destroy(HybridConnection *conn)
{
    if (conn) {
        g_free(conn->host);
        g_free(conn);
        if (conn->sk > 0) {
            close(conn->sk);
        }
    }

}
