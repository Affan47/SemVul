read_body_with_length(HTTPEntity *ent, Connection *conn)
{
    Octstr *os;

    os = conn_read_fixed(conn, ent->expected_body_len);
    if (os == NULL) {
        if (conn_error(conn) || conn_eof(conn))
            ent->state = body_error;
        return;
    }
    octstr_destroy(ent->body);
    ent->body = os;
    ent->state = entity_done;
}
