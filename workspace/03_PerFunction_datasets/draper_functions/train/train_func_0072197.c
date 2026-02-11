ackRead ()
{
    d->readsignalon = true;
    if ( d->needreadsignal || d->recvbuffer.length() != 0 ) {
        controlledEmission();
    }
}
