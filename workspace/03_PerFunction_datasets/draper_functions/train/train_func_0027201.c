um_account_dialog_finalize (GObject *obj)
{
        UmAccountDialog *self = UM_ACCOUNT_DIALOG (obj);

        if (self->cancellable)
                g_object_unref (self->cancellable);
        g_object_unref (self->enterprise_realms);

        G_OBJECT_CLASS (um_account_dialog_parent_class)->finalize (obj);
}
