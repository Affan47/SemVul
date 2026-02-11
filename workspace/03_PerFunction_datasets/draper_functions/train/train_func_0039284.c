rot_selected_cb (GtkComboBox *box, gpointer data)
{
    GtkRotCtrl *ctrl = GTK_ROT_CTRL (data);


    if (ctrl->conf != NULL) {
        g_free (ctrl->conf->name);
        g_free (ctrl->conf->host);
        g_free (ctrl->conf);
    }

    ctrl->conf = g_try_new (rotor_conf_t, 1);
    if (ctrl->conf == NULL) {
        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s:%d: Failed to allocate memory for rotator config"),
                     __FILE__, __LINE__);
        return;
    }


    ctrl->conf->name = gtk_combo_box_get_active_text (box);
    if (rotor_conf_read (ctrl->conf)) {
        sat_log_log (SAT_LOG_LEVEL_MSG,
                     _("Loaded new rotator configuration %s"),
                     ctrl->conf->name);


        gtk_rot_knob_set_range (GTK_ROT_KNOB (ctrl->AzSet), ctrl->conf->minaz, ctrl->conf->maxaz);
        gtk_rot_knob_set_range (GTK_ROT_KNOB (ctrl->ElSet), ctrl->conf->minel, ctrl->conf->maxel);


        set_flipped_pass(ctrl);
    }
    else {
        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s:%d: Failed to load rotator configuration %s"),
                     __FILE__, __LINE__, ctrl->conf->name);

        g_free (ctrl->conf->name);
        if (ctrl->conf->host)
            g_free (ctrl->conf->host);
        g_free (ctrl->conf);
        ctrl->conf = NULL;
    }
}
