push_if_state(struct expr *arg)
{
    int val;
    LOG(LOG_DEBUG, ("resolving if expression\n"));
    val = resolve_expr(arg);
    LOG(LOG_DEBUG, ("if expr resolved to %d\n", val));
    if(val)
    {
        push_state_init = 1;
    }
    else
    {
        push_state_skip = 1;
    }
}
