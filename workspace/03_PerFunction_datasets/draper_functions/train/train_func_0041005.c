action_handle_string(event_t *ev, action_t *action)
{
    USE_VAR(ev);
    REQUIRE_RVAL(action->param.string != NULL, 0);
    cmd_write((unsigned char *) action->param.string, strlen(action->param.string));
    return 1;
}
