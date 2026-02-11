errorMapFetchComplete(ErrorMapState * state)
{
    storeClientUnregister(state->sc, state->e, state);
    state->sc = NULL;
    storeUnlockObject(state->e);
    state->e = NULL;
    requestUnlink(state->req);
    state->req = NULL;
    cbdataUnlock(state->callback_data);
    state->callback_data = NULL;
    cbdataFree(state);
}
