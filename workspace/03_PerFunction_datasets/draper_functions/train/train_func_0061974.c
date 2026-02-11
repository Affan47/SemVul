on_mode_changed(GtkRadioAction* act, GtkRadioAction *current, FmSidePane* sp)
{
    FmSidePaneMode mode = gtk_radio_action_get_current_value(act);
    if(mode != sp->mode)
        fm_side_pane_set_mode(sp, mode);
}
