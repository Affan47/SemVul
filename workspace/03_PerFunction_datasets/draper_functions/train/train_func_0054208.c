writeRemoteAuth(FILE *file, Xauth *auth, XdmcpNetaddr peer, int peerlen,
                const char *name, int *ok)
{
    int family = FamilyLocal;
    CARD8 *addr;

    debug("writeRemoteAuth: %s %.*s\n", name, auth->name_length, auth->name);
    if (!peer || peerlen < 2)
        return;
    setAuthNumber(auth, name);
    family = convertAuthAddr(peer, &peerlen, &addr);
    debug("writeRemoteAuth: family %d\n", family);
    if (family != FamilyLocal) {
        debug("writeRemoteAuth: %d, %02[*:hhx\n",
              family, peerlen, addr);
        writeAddr(family, peerlen, addr, file, auth, ok);
    } else
        writeLocalAuth(file, auth, name, ok);
}
