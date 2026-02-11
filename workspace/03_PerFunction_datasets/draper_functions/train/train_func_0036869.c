protocolDirective(MaState *state, cchar *key, cchar *value)
{
    httpSetHostProtocol(state->host, value);
    if (!scasematch(value, "HTTP/1.0") && !scasematch(value, "HTTP/1.1")) {
        mprError("Unknown http protocol %s. Should be HTTP/1.0 or HTTP/1.1", value);
        return MPR_ERR_BAD_SYNTAX;
    }
    return 0;
}
