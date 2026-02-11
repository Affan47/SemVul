drive_button_dispose (GObject *object)
{
    DriveButton *self = DRIVE_BUTTON (object);

    drive_button_set_volume (self, NULL);

    if (self->update_tag)
	g_source_remove (self->update_tag);
    self->update_tag = 0;

    drive_button_reset_popup (self);

    G_OBJECT_CLASS (drive_button_parent_class)->dispose (object);
}
