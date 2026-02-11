rpc_transport_get_peername (rpc_transport_t *this, char *hostname, int hostlen)
{
        int32_t ret = -1;
        GF_VALIDATE_OR_GOTO ("rpc", this, out);

        ret = this->ops->get_peername (this, hostname, hostlen);
out:
        return ret;
}
