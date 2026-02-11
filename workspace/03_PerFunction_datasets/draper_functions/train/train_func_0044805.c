usage_system_command_finalize (UsageSystemCommand* obj) {
	UsageSystemCommand * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, USAGE_TYPE_SYSTEM_COMMAND, UsageSystemCommand);
	usage_system_command_dequeue (self);
	(self->priv->callback_target_destroy_notify == NULL) ? NULL : (self->priv->callback_target_destroy_notify (self->priv->callback_target), NULL);
	self->priv->callback = NULL;
	self->priv->callback_target = NULL;
	self->priv->callback_target_destroy_notify = NULL;
}
