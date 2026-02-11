actions_parse_string(const gchar *name)
{
    ObActionsAct *act = NULL;

    if ((act = actions_build_act_from_string(name))) {
        if (act->def->canbeinteractive) {
            if (act->def->setup.i)
                act->options = act->def->setup.i(NULL,
                                                 &act->i_pre,
                                                 &act->i_input,
                                                 &act->i_cancel,
                                                 &act->i_post);
        }
        else {
            if (act->def->setup.n)
                act->options = act->def->setup.n(NULL);
        }
    }


    return act;
}
