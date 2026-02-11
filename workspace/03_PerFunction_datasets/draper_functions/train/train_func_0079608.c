free_externalAclState(void *data)
{
    externalAclState *state = data;
    safe_free(state->key);
    cbdataUnlock(state->callback_data);
    cbdataUnlock(state->def);
}
