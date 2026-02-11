ntb_connection_add_addr_address(struct ntb_connection *conn,
                                int64_t timestamp,
                                uint32_t stream,
                                uint64_t services,
                                const struct ntb_netaddress *address)
{
        int n_hashes = get_n_hashes_for_addr(conn);


        if (n_hashes >= 0xfc) {
                ntb_connection_end_addr(conn);
                ntb_connection_begin_addr(conn);
        }

        ntb_proto_add_64(&conn->out_buf, timestamp);
        ntb_proto_add_32(&conn->out_buf, stream);
        ntb_proto_add_64(&conn->out_buf, services);
        ntb_proto_add_netaddress(&conn->out_buf, address);
}
