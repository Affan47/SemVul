rpc_clnt_start (struct rpc_clnt *rpc)
{
        struct rpc_clnt_connection *conn = NULL;

        if (!rpc)
                return -1;

        conn = &rpc->conn;

        rpc_clnt_reconnect (conn->trans);

        return 0;
}
