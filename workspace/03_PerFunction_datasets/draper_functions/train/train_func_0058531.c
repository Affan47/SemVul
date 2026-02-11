actions_run_acts(GSList *acts,
                      ObUserAction uact,
                      guint state,
                      gint x,
                      gint y,
                      gint button,
                      ObFrameContext con,
                      struct _ObClient *client)
{
    GSList *it;
    gboolean update_user_time;


    if (uact == OB_USER_ACTION_MENU_SELECTION)
        state = 0;

    if (x < 0 && y < 0)
        screen_pointer_pos(&x, &y);

    update_user_time = FALSE;
    for (it = acts; it; it = g_slist_next(it)) {
        ObActionsData data;
        ObActionsAct *act = it->data;
        gboolean ok = TRUE;

        actions_setup_data(&data, uact, state, x, y, button, con, client);


        if (!interactive_act || interactive_act->def->run != act->def->run) {
            if (actions_act_is_interactive(act)) {

                if (interactive_act)
                    actions_interactive_cancel_act();
                if (act->i_pre)
                    if (!act->i_pre(state, act->options))
                        act->i_input = NULL;
            }

            if (actions_act_is_interactive(act))
                ok = actions_interactive_begin_act(act, state);
        }


        if (ok) {
            if (!act->def->run(&data, act->options)) {
                if (actions_act_is_interactive(act))
                    actions_interactive_end_act();
                if (client && client == focus_client &&
                    act->def->modifies_focused_window)
                {
                    update_user_time = TRUE;
                }
            } else {

                g_assert(act->i_input);


                break;
            }
        }
    }
    if (update_user_time)
        event_update_user_time();
}
