sasl_auxprop_getctx(sasl_conn_t *conn)
{
    sasl_server_conn_t *sconn;

    if(!conn || conn->type != SASL_CONN_SERVER) return NULL;

    sconn = (sasl_server_conn_t *)conn;

    return sconn->sparams->propctx;
}
