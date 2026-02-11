netsnmp_unix_send(netsnmp_transport *t, void *buf, int size,
                  void **opaque, int *olength)
{
    int rc = -1;

    if (t != NULL && t->sock >= 0) {
        DEBUGMSGTL(("netsnmp_unix", "send %d bytes to %p on fd %d\n",
                    size, buf, t->sock));
        while (rc < 0) {
            rc = sendto(t->sock, buf, size, 0, NULL, 0);
            if (rc < 0 && errno != EINTR) {
                break;
            }
        }
    }
    return rc;
}
