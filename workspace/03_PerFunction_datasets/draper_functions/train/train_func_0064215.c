pokeFdEvent(int fd, int status, int what)
{
    TimeEventHandlerPtr handler;
    FdEventHandlerPokeRec poke;

    poke.fd = fd;
    poke.status = status;
    poke.what = what;

    handler = scheduleTimeEvent(0, pokeFdEventHandler,
                                sizeof(poke), &poke);
    if(!handler) {
        do_log(L_ERROR, "Couldn't allocate handler.\n");
    }
}
