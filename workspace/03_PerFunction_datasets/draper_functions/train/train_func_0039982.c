ssl_cmd_SSLCACertificateFile(cmd_parms *cmd,
                                         void *dcfg,
                                         const char *arg)
{

    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    if (cmd->path) {
        return NO_PER_DIR_SSL_CA;
    }


    sc->server->auth.ca_cert_file = arg;

    return NULL;
}
