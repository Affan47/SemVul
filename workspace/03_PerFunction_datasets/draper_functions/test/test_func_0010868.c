_e_mod_action_adjust_transitions(E_Object   *obj __UNUSED__,
                                 const char *params __UNUSED__)
{
    E_Desk *desk;

    desk = get_current_desk();
    if (!desk)
        return;

    check_tinfo(desk);
    if (!_G.tinfo->conf || !_G.tinfo->conf->nb_stacks) {
        return;
    }

    _do_transition_overlay();
}
