storeUfsClose(SwapDir * SD, storeIOState * sio)
{
    ufsstate_t *ufsstate = (ufsstate_t *) sio->fsstate;

    debug(79, 3) ("storeUfsClose: dirno %d, fileno %08X, FD %d\n",
	sio->swap_dirn, sio->swap_filen, ufsstate->fd);
    if (ufsstate->flags.reading || ufsstate->flags.writing) {
	ufsstate->flags.close_request = 1;
	return;
    }
    storeUfsIOCallback(sio, 0);
}
