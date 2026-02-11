sk_proxy_write_oob (Socket s, const char *data, int len)
{
    Proxy_Socket ps = (Proxy_Socket) s;

    if (ps->state != PROXY_STATE_ACTIVE) {
	bufchain_clear(&ps->pending_output_data);
	bufchain_clear(&ps->pending_oob_output_data);
	bufchain_add(&ps->pending_oob_output_data, data, len);
	return len;
    }
    return sk_write_oob(ps->sub_socket, data, len);
}
