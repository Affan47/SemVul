auth_cb (PasswdHandler    *handler,
         GError           *error,
         UmPasswordDialog *um)
{
        if (error) {
                um->old_password_ok = FALSE;
                set_entry_validation_error (GTK_ENTRY (um->old_password_entry),
                                            _("Wrong password"));
        }
        else {
                um->old_password_ok = TRUE;
                clear_entry_validation_error (GTK_ENTRY (um->old_password_entry));
        }

        update_sensitivity (um);
}
