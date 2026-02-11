actions_interactive_input_event(XEvent *e)
{
    gboolean used = FALSE;
    if (interactive_act) {
        if (!interactive_act->i_input(interactive_initial_state, e,
                                      grab_input_context(),
                                      interactive_act->options, &used))
        {
            used = TRUE;

            actions_interactive_end_act();
        }
    }
    return used;
}
