read_body_until_eof(HTTPEntity *ent, Connection *conn)
{
    Octstr *os;

    while ((os = conn_read_everything(conn)) != NULL) {
        octstr_append(ent->body, os);
        octstr_destroy(os);
    }
    if (conn_error(conn))
	ent->state = body_error;
    if (conn_eof(conn))
	ent->state = entity_done;
}
