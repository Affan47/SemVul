Bind(const char* dir, const char* name, int which)
{
    struct sockaddr_un addr;

    if ((fSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        jack_error("Cannot create server socket err = %s", strerror(errno));
        return -1;
    }

    addr.sun_family = AF_UNIX;

    BuildName(name, fName, dir, which, sizeof(addr.sun_path));
    strncpy(addr.sun_path, fName, sizeof(addr.sun_path) - 1);

    jack_log("JackServerSocket::Bind : addr.sun_path %s", addr.sun_path);
    unlink(fName);

    if (bind(fSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        jack_error("Cannot bind server to socket err = %s", strerror(errno));
        goto error;
    }

    if (listen(fSocket, 100) < 0) {
        jack_error("Cannot enable listen on server socket err = %s", strerror(errno));
        goto error;
    }

    return 0;

error:
    unlink(fName);
    close(fSocket);
    return -1;
}
