is_tls_protocol(const char *p, int len, struct proto *proto)
{


    return p[0] == 0x16 && p[1] == 0x03 && ( p[2] >= 0 && p[2] <= 0x03);
}
