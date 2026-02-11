brasero_tool_dialog_drive_changed_cb (BraseroMediumSelection *selection,
				      BraseroMedium *medium,
				      BraseroToolDialog *self)
{
	BraseroToolDialogClass *klass;

	klass = BRASERO_TOOL_DIALOG_GET_CLASS (self);
	if (klass->medium_changed)
		klass->medium_changed (self, medium);
}
