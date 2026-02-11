AuCopySwapElementWrite(ClientPtr client, int size, auElement * p)
{
    auElement *e;

    if (!(e = (auElement *) aualloc(size)))
        return;

    bcopy(p, e, size);
    SwapElement(e, AuFalse);
    (void) WriteToClient(client, size, (char *) e);

    aufree(e);
}
