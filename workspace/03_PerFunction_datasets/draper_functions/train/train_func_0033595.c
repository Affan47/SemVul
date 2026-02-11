glusterd_nodesvc_disconnect (char *server)
{
        struct rpc_clnt         *rpc = NULL;

        rpc = glusterd_nodesvc_get_rpc (server);

        if (rpc) {
                rpc_clnt_connection_cleanup (&rpc->conn);
                rpc_clnt_unref (rpc);
                (void)glusterd_nodesvc_set_rpc (server, NULL);
        }

        return 0;
}
