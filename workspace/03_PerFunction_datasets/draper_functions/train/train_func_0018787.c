ssh_gssapi_get_creds(ssh_session session){
    if (!session || !session->gssapi || session->gssapi->client_creds == GSS_C_NO_CREDENTIAL)
        return NULL;
    return (ssh_gssapi_creds)session->gssapi->client_creds;
}
