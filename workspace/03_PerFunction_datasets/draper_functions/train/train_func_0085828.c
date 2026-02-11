apply_now_clicked(GtkButton* button, gpointer user_data)
{
    GError* err = NULL;
    ui_data_t* ui = user_data;
    gboolean ok = validate_user_pin_config(ui, &err);
    if (ok)
        apply_changes_reconfig(ui->sysfs_pins, ui->sysfs_pincount,
            ui->current_codec->card, ui->current_codec->device,
            ui->model_auto ? "auto" : NULL, &err);
    show_action_result(ui, err,
        "Ok, now go ahead and test to see if it actually worked!\n"
        "(Remember, this stuff is still experimental.)");
}
