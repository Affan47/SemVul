___device_select_add_timeout
   ___P((___device_select_state *state,
         int i,
         ___time timeout),
        (state,
         i,
         timeout)
___device_select_state *state;
int i;
___time timeout;)
{
  if (___time_less (timeout, state->timeout))
    state->timeout = timeout;
}
